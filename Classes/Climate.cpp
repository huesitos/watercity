#include "Climate.h"
#include "ResourceManager.h"


Climate::Climate()
{
  climate = 0;

  rain_chance_sunny = 5;
  rain_chance_cloudy = 20;
  rain_chance_rainy = 40;
}

void Climate::rain()
{
  int chance = RandomHelper::random_int(0, 100);
  auto &rm = ResourceManager::getInstance();

  if (climate == SUNNY and rain_chance_sunny > chance)
  {
    int water_increase = RandomHelper::random_int(500, 1000);
    rm.increase_water_reserves(water_increase);
  }
  else if (climate == CLOUDY and rain_chance_cloudy > chance)
  {
    int water_increase = RandomHelper::random_int(1000, 1500);
    rm.increase_water_reserves(water_increase);
  }
  else if (climate == RAINY and rain_chance_rainy > chance)
  {
    int water_increase = RandomHelper::random_int(1500, 2000);
    rm.increase_water_reserves(water_increase);
  }
}

void Climate::set_week_climate()
{
  int chance = RandomHelper::random_int(0, 100);

  if (chance < 10)
  {
    climate = SUNNY;
  }
  else if (chance < 80)
  {
    climate = CLOUDY;
  }
  else
  {
    climate = RAINY;
  }
}

int Climate::get_climate()
{
  return climate;
}