#include "settings.h"

const SettingParams pomodoro_duration_params = {
    .default_value = 25,
    .min_value = 1,
    .max_value = 60,
    .title = "Pomodoro Duration",
    .format = "%u min."
};

const SettingParams break_duration_params = {
    .default_value = 5,
    .min_value = 1,
    .max_value = 30,
    .title = "Break Duration",
    .format = "%u min."
};

const SettingParams long_break_enabled_params = {
    .default_value = true,
    .title = "Long Break"
};

const SettingParams long_break_duration_params = {
    .default_value = 15,
    .min_value = 1,
    .max_value = 60,
    .title = "Long Break Duration",
    .format = "%u min."
};

const SettingParams long_break_delay_params = {
    .default_value = 4,
    .min_value = 2,
    .max_value = 9,
    .title = "Long Break Delay",
    .format = "%u"
};

int32_t read_int(const uint32_t key, int32_t def_value) {
  if (persist_exists(key)) {
    return persist_read_int(key);
  } else {
    return def_value;
  }
}

bool read_bool(const uint32_t key, int32_t def_value) {
  if (persist_exists(key)) {
    return persist_read_bool(key);
  } else {
    return def_value;
  }
}

Calendar read_calendar(const uint32_t key, Calendar def_value) {
  if (persist_exists(key)) {
    Calendar calendar;
    persist_read_data(key, &calendar, sizeof(calendar));
    return calendar;
  } else {
    return def_value;
  }
}

TomatoSettings get_default_settings() {
  TomatoSettings default_settings = {
    .last_time = time(NULL),
    .state = STATE_DEFAULT,
    .calendar = CALENDAR_DEFAULT,
    .pomodoro_duration = pomodoro_duration_params.default_value,
    .break_duration = break_duration_params.default_value,
    .long_break_enabled = long_break_enabled_params.default_value,
    .long_break_duration = long_break_duration_params.default_value,
    .long_break_delay = long_break_delay_params.default_value,
    .end_time = 0,
    .wakeup_id = -1, 
  };
  
  return default_settings;
}

TomatoSettings read_settings() {
  TomatoSettings default_settings = get_default_settings();
  
  TomatoSettings settings = {
    .last_time = read_int(LAST_TIME_KEY, default_settings.last_time),
    .state = read_int(STATE_KEY, default_settings.state),
    .calendar = read_calendar(CALENDAR_KEY, default_settings.calendar),
    .pomodoro_duration = read_int(POMODORO_DURATION_KEY, default_settings.pomodoro_duration),
    .break_duration = read_int(BREAK_DURATION_KEY, default_settings.break_duration),
    .long_break_enabled = read_bool(LONG_BREAK_ENABLED_KEY, default_settings.long_break_enabled),
    .long_break_duration = read_int(LONG_BREAK_DURATION_KEY, default_settings.long_break_duration),
    .long_break_delay = read_int(LONG_BREAK_DELAY_KEY, default_settings.long_break_delay),
    .end_time = read_int(END_TIME_KEY, default_settings.end_time),
    .wakeup_id = read_int(WAKEUP_ID_KEY, default_settings.wakeup_id),
  };
  
  int time_passed = default_settings.last_time - settings.last_time;

  if (time_passed > MAX_ITERATION_IDLE) {
    settings.calendar = default_settings.calendar;
  }
  
  if (time_passed > MAX_APP_IDLE) {
    settings.last_time = default_settings.last_time;
    settings.state = default_settings.state;
  }
  
  return settings;
}

void save_settings(TomatoSettings settings) {
  persist_write_int(LAST_TIME_KEY, settings.last_time);
  persist_write_int(STATE_KEY, settings.state);
  Calendar calendar = settings.calendar;
  persist_write_data(CALENDAR_KEY, &calendar, sizeof(calendar));
  persist_write_int(END_TIME_KEY, settings.end_time);
  persist_write_int(WAKEUP_ID_KEY, settings.wakeup_id);
}

void reset_settings(void) {
  persist_delete(LAST_TIME_KEY);
  persist_delete(STATE_KEY);
  persist_delete(CALENDAR_KEY);
  persist_delete(POMODORO_DURATION_KEY);
  persist_delete(BREAK_DURATION_KEY);
  persist_delete(LONG_BREAK_ENABLED_KEY);
  persist_delete(LONG_BREAK_DURATION_KEY);
  persist_delete(LONG_BREAK_DELAY_KEY);
  persist_delete(END_TIME_KEY);
  persist_delete(WAKEUP_ID_KEY);
}
