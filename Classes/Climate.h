#ifndef __CLIMATE_H__
#define __CLIMATE_H__

#include "cocos2d.h"
#include <iostream>

USING_NS_CC;

class Climate
{
public:
  static Climate& getInstance()
  {
    static Climate *climate = new Climate;
    return *climate;
  }

  const int SUNNY = 0;
  const int CLOUDY = 1;
  const int RAINY = 2;

  void rain();
  void set_week_climate();
  int get_climate();
  Sprite* get_climate_sprite();

private:
  Climate();

  // 0 is sunny
  // 1 is cloudy
  // 2 is rainny
  int climate;

  int rain_chance_sunny;
  int rain_chance_cloudy;
  int rain_chance_rainy;
};

#endif // __CLIMATE_H__
