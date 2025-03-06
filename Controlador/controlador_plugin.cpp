#include <functional>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/sensors/sensors.hh>
#include <gazebo/common/common.hh>
#include <ignition/math/Vector3.hh>

namespace gazebo
{
    class ControladorPlugin : public ModelPlugin
    {
    public:
        void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf)
        {
            model = _model;

            leftJoint = _model->GetJoint("left_wheel_hinge");
            rightJoint = _model->GetJoint("right_wheel_hinge");

            if (!leftJoint)
                gzerr << "Unable to find left joint[left_wheel_hinge]\n";
            if (!rightJoint)
                gzerr << "Unable to find right joint[right_wheel_hinge]\n";

            sensor = std::dynamic_pointer_cast<sensors::RaySensor>(
                sensors::SensorManager::Instance()->GetSensor("my_sensor"));

            if (!sensor)
                gzerr << "Unable to find sensor[my_sensor]\n";

            updateConnection = event::Events::ConnectWorldUpdateBegin(std::bind(&ControladorPlugin::OnUpdate, this));

            isRotating = false;
            rotationStartTime = 0;
            rotationDuration = 2.43;
        }

        void OnUpdate()
        {
            if (!sensor || !sensor->IsActive()) return;

            double currentTime = model->GetWorld()->SimTime().Double();

            ignition::math::Pose3d pose = model->WorldPose();
            double x = pose.Pos().X();
            double y = pose.Pos().Y();

            if (x >= 1.0 && x <= 2.0 && y >= 1.0 && y <= 2.0)
            {
            SetWheelVelocities(0.0, 0.0);  // Stop the robot
            printf("He llegado a la meta: %f %f\n", x, y);
            return;
            }

            if (isRotating)
            {
            if (currentTime - rotationStartTime >= rotationDuration)
            {
                isRotating = false;
                SetWheelVelocities(1.0, 1.0);
            }
            else
            {
                SetWheelVelocities(-1.0, 1.0);  // Rotate in place
            }
            }
            else
            {
            UpdateMovement();
            }

            printf("At: %f %f %f\n", x, y, pose.Pos().Z());
        }

    private:
        physics::ModelPtr model;
        physics::JointPtr leftJoint, rightJoint;
        sensors::RaySensorPtr sensor;
        event::ConnectionPtr updateConnection;
        bool isRotating;
        double rotationStartTime;
        double rotationDuration;

        void SetWheelVelocities(double left, double right)
        {
            leftJoint->SetVelocity(0, left);
            rightJoint->SetVelocity(0, right);
        }

        void UpdateMovement()
        {
            std::vector<double> ranges;
            sensor->Ranges(ranges);

            int centerIndex = ranges.size() / 2;
            int rangeToCheck = 5;
            
            double minFrontalDistance = sensor->RangeMax();
            
            for (int i = centerIndex - rangeToCheck; i <= centerIndex + rangeToCheck; i++)
            {
                if (i >= 0 && i < ranges.size() && ranges[i] < minFrontalDistance)
                {
                    minFrontalDistance = ranges[i];
                }
            }

            bool wallInFront = minFrontalDistance < 0.4;

            if (wallInFront)
            {
                isRotating = true;
                rotationStartTime = model->GetWorld()->SimTime().Double();
                SetWheelVelocities(-1.0, 1.0);  // Start rotating
            }
            else
            {
                SetWheelVelocities(1.0, 1.0);  // Move forward
            }
        }
    };

    GZ_REGISTER_MODEL_PLUGIN(ControladorPlugin)
}

