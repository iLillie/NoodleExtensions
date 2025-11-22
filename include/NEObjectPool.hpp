// https://github.com/Kautenja/object-pool/blob/master/include/object_pool.hpp

#pragma once

#include <list>
#include "Animation/NoodleMovementDataProvider.hpp"
#include "GlobalNamespace/BeatmapObjectData.hpp"
#include "NELogger.h"

namespace NoodleExtensions::Pool {

class NoodleMovementDataProviderPool {
private:
  std::deque<SafePtr<NoodleMovementDataProvider>> free = {};

public:
  NoodleMovementDataProviderPool(int count) : free() {
    for (int i = 0; i < count; ++i) {
      put(NoodleMovementDataProvider::New_ctor());
    }
  }

  SafePtr<NoodleMovementDataProvider> get(GlobalNamespace::BeatmapObjectData* beatmapObjectData) {
    if (free.empty()) {
      auto obj = SafePtr(NoodleMovementDataProvider::New_ctor());
      obj->InitObject(beatmapObjectData);
      put(obj);
      return obj;
    }

    SafePtr<NoodleMovementDataProvider> obj = free.back();
    free.pop_back();
    obj->InitObject(beatmapObjectData);
    return obj;
  }

  void put(SafePtr<NoodleMovementDataProvider> obj) {
    // reset variables here if needed
    obj->InitObject(nullptr);
    free.emplace_back(obj);
  }
};

} // namespace NoodleExtensions::Pool
