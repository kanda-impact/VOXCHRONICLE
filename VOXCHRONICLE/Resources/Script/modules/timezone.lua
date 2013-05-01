TimeZoneDay = 0
TimeZoneSunset = 1
TimeZoneNight = 2
function getCurrentTimeZone()
  local time = VQTime:sharedTime()
  local hour = time:getCurrentHour()
  if 6 <= hour and hour < 16 then -- 朝
    return TimeZoneDay
  elseif 16 <= hour and hour < 19 then -- 夕方
    return TimeZoneSunset
  end
  return TimeZoneNight -- 夜
end
