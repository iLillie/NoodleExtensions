#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "custom-json-data/shared/CustomBeatmapData.h"
#include "beatsaber-hook/shared/utils/hooking.hpp"

#include "GlobalNamespace/MissionLevelScenesTransitionSetupDataSO.hpp"
#include "GlobalNamespace/EnvironmentsListModel.hpp"

#include "Animation/ParentObject.h"
#include "NEHooks.h"
#include "NECaches.h"
#include "SceneTransitionHelper.hpp"

using namespace GlobalNamespace;
using namespace TrackParenting;
using namespace CustomJSONData;
using namespace NoodleExtensions;

MAKE_HOOK_MATCH(
    MissionLevelScenesTransitionSetupDataSO_Init,
        &::GlobalNamespace::MissionLevelScenesTransitionSetupDataSO::Init,
        void, MissionLevelScenesTransitionSetupDataSO* self,
        ::StringW missionId, ::ByRef<::GlobalNamespace::BeatmapKey> beatmapKey, ::GlobalNamespace::BeatmapLevel* beatmapLevel,
        ::ArrayW<::GlobalNamespace::MissionObjective*, ::Array<::GlobalNamespace::MissionObjective*>*> missionObjectives,
        ::GlobalNamespace::ColorScheme* playerOverrideColorScheme, bool playerOverrideLightshowColors,
        ::GlobalNamespace::GameplayModifiers* gameplayModifiers, ::GlobalNamespace::PlayerSpecificSettings* playerSpecificSettings,
        ::GlobalNamespace::EnvironmentsListModel* environmentsListModel,
        ::GlobalNamespace::AudioClipAsyncLoader* audioClipAsyncLoader, ::GlobalNamespace::SettingsManager* settingsManager,
        ::GlobalNamespace::BeatmapDataLoader* beatmapDataLoader, ::StringW backButtonText,
        ::GlobalNamespace::BeatmapLevelsModel* beatmapLevelsModel, ::GlobalNamespace::IBeatmapLevelData* beatmapLevelData) {

  auto customBeatmapLevel = il2cpp_utils::try_cast<SongCore::SongLoader::CustomBeatmapLevel>(beatmapLevel);
  if (!customBeatmapLevel) {
    MissionLevelScenesTransitionSetupDataSO_Init(self, missionId, beatmapKey, beatmapLevel, missionObjectives, playerOverrideColorScheme,
      playerOverrideLightshowColors, gameplayModifiers, playerSpecificSettings, environmentsListModel, audioClipAsyncLoader,
      settingsManager, beatmapDataLoader, backButtonText, beatmapLevelsModel, beatmapLevelData);
    return;
  }

  auto environmentInfoBySerializedNameSafe = environmentsListModel->GetEnvironmentInfoBySerializedNameSafe(
      beatmapLevel->GetEnvironmentName(beatmapKey->beatmapCharacteristic, beatmapKey->difficulty)._environmentName);

  // TODO: Fix environment override
  SceneTransitionHelper::Patch(customBeatmapLevel.value(), beatmapKey.heldRef, environmentInfoBySerializedNameSafe, playerSpecificSettings);

  MissionLevelScenesTransitionSetupDataSO_Init(self, missionId, beatmapKey, beatmapLevel, missionObjectives, playerOverrideColorScheme,
     playerOverrideLightshowColors, gameplayModifiers, playerSpecificSettings, environmentsListModel, audioClipAsyncLoader,
     settingsManager, beatmapDataLoader, backButtonText, beatmapLevelsModel, beatmapLevelData);
}

void InstallMissionLevelScenesTransitionSetupDataSOHooks() {
  INSTALL_HOOK(NELogger::Logger, MissionLevelScenesTransitionSetupDataSO_Init);
}
NEInstallHooks(InstallMissionLevelScenesTransitionSetupDataSOHooks);