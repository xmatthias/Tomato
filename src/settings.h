#define POMODORO_STATE 0
#define BREAK_STATE 1
  
#define RUNNING_EXEC_STATE 0
#define PAUSED_EXEC_STATE 1
  
#define MAX_APP_IDLE (30 * 60)
#define MAX_ITERATION_IDLE (8 * 60 * 60)

#define INCREMENT_TIME 60


#define LAST_TIME_KEY 0
#define STATE_KEY 1
//#define CURRENT_DURATION_KEY 2
#define CALENDAR_KEY 3
#define POMODORO_DURATION_KEY 4
#define BREAK_DURATION_KEY 5
#define LONG_BREAK_ENABLED_KEY 6
#define LONG_BREAK_DURATION_KEY 7
#define LONG_BREAK_DELAY_KEY 8
#define END_TIME_KEY 9
#define WAKEUP_ID_KEY 10

#define LAST_TIME_DEFAULT 0
#define STATE_DEFAULT 0
#define CALENDAR_DEFAULT ((Calendar){time(NULL), {}})
  
#include "pebble.h"
  
#ifndef SETTINGS_H
#define SETTINGS_H

typedef struct SettingParams {
  int default_value;
  int min_value;
  int max_value;
  char* title;
  char* format;
} SettingParams;

extern const SettingParams pomodoro_duration_params;
extern const SettingParams break_duration_params;
extern const SettingParams long_break_enabled_params;
extern const SettingParams long_break_duration_params;
extern const SettingParams long_break_delay_params;

typedef struct Calendar {
  int start_time;
  uint8_t sets[100];
} __attribute__((__packed__)) Calendar;

typedef struct TomatoSettings {
  int last_time;
  int state;
  Calendar calendar;
  int pomodoro_duration;
  int break_duration;
  bool long_break_enabled;
  int long_break_duration;
  int long_break_delay;
  time_t end_time;
  WakeupId wakeup_id;
} TomatoSettings;

TomatoSettings get_default_settings();

TomatoSettings read_settings();

void save_settings(TomatoSettings settings);

void reset_settings(void);

#endif /* SETTINGS_H */
