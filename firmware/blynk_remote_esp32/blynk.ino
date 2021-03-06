void report_status()
{
  Blynk.virtualWrite(V40, (abs(leftbelt_current) + abs(rightbelt_current)) / 2);
  Blynk.virtualWrite(V41, (abs(leftbelt_setpoint) + abs(rightbelt_setpoint)) / 2);
  Blynk.virtualWrite(V42, get_battery_voltage());
}

void setSmoothing(int s)
{
  smoothing = min(1000.0, max(1.0, s / 100.0));
}

BLYNK_WRITE(V9) // Smoothing
{
  int s = param.asInt();

  if (s > 0)
    setSmoothing(s);
}

BLYNK_WRITE(V1)
{
  leftbelt_setpoint = param.asInt();
  there_is_activity();
}

BLYNK_WRITE(V2)
{
  rightbelt_setpoint = param.asInt();
  there_is_activity();
}

BLYNK_WRITE(V11) // X speed
{
  remote_x = max(-100, min(100, param.asInt()));
}
BLYNK_WRITE(V12) // Y speed
{
  remote_y = max(-100, min(100, param.asInt()));
}

BLYNK_WRITE(V13) // time delay and execute
{
  int running_time = min(10000, param.asInt());

  if (running_time > 0)
  {
    setMotorsDirection(remote_x, remote_y);
    remote_stop = millis() + running_time;
  }
}

// Basic (Joystick)
BLYNK_WRITE(V10)
{
  setMotorsDirection(-param[0].asInt(), -param[1].asInt());
  there_is_activity();
}

BLYNK_WRITE(V4) // Stop
{
  if (param.asInt() == 1)
    stop_all();
}

BLYNK_WRITE(V5) // Kill switch
{
  int p = param.asInt();

  if (p)
    stop_all();

  stop_all_signals_to_motors = p;
}


BLYNK_WRITE(V3)
{
  play_melody(param.asInt());
}
