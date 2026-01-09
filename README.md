# PX4 to ROS2 GPS bridge

## Description
This node acts as a bridge between PX4 Autopilot and ROS 2.   
It subscribes to ('px4_msgs') and republishes as ('sensor_msgs/NavSatFix') message.

### Subscribed Topics:
* Topic: `/fmu/out/vehicle_gps_position`
  * Message: `px4_msgs/SensorGps`

### Published Topics:
* Topic: `/gps/fix`
  * Message: `sensor_msgs/NavSatFix`
  * Data Mapping:
    * **`header.frame_id`**: Always set to `"gps_link"`.
    * **`status.status`**:
      * `STATUS_FIX` (0) — if PX4 reports `fix_type >= 3` (3D Fix).
      * `STATUS_NO_FIX` (-1) — if PX4 reports `fix_type < 3`.
    * **`latitude`**: Flight controller latitude (degrees).
    * **`longitude`**: Flight controller longitude (degrees).
    * **`altitude`**: Altitude above Mean Sea Level (meters).
    * **`position_covariance`**: Not populated (defaults to 0).
    * **`position_covariance_type`**: `COVARIANCE_TYPE_UNKNOWN` (0).
