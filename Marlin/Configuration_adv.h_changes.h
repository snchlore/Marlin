  #define BLTOUCH_SET_5V_MODE
    #define BLTOUCH_HS_MODE
    #define BLTOUCH_FORCE_SW_MODE
#define ADVANCED_PAUSE_FEATURE
  #define PAUSE_PARK_RETRACT_LENGTH            6  // (mm) Initial retract.
                                                  // This short retract is done immediately, before parking the nozzle.
  #define FILAMENT_CHANGE_UNLOAD_FEEDRATE     60  // (mm/s) Unload filament feedrate. This can be pretty fast.
  #define FILAMENT_CHANGE_UNLOAD_ACCEL        10  // (mm/s^2) Lower acceleration may allow a faster feedrate.
  #define FILAMENT_CHANGE_UNLOAD_LENGTH      300  