#include "Rain.h"
#include "ResourceManager.h"

USING_NS_CC;

void Rain::rain()
{
  int will_it_rain = RandomHelper::random_int(0, 100);

  if (will_it_rain == 2)
  {
    int water_increase = RandomHelper::random_int(10000, 30000);
    auto &rm = ResourceManager::getInstance();
    rm.increase_water_reserves(water_increase);
    printf("It rained\n");
  }
}