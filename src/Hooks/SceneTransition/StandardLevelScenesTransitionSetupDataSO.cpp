#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "custom-json-data/shared/CustomBeatmapData.h"
#include "beatsaber-hook/shared/utils/hooking.hpp"

#include "GlobalNamespace/StandardLevelScenesTransitionSetupDataSO.hpp"

#include "custom-json-data/shared/CustomBeatmapSaveDatav3.h"

#include "Animation/ParentObject.h"
#include "NEHooks.h"
#include "NECaches.h"
#include "SceneTransitionHelper.hpp"

using namespace GlobalNamespace;
using namespace TrackParenting;
using namespace CustomJSONData;
using namespace NoodleExtensions;

MAKE_HOOK_MATCH(StandardLevelScenesTransitionSetupDataSO_Init,
                &StandardLevelScenesTransitionSetupDataSO::Init, void,
                StandardLevelScenesTransitionSetupDataSO* self,
                ::StringW gameMode, ::ByRef<::GlobalNamespace::BeatmapKey> beatmapKey, ::GlobalNamespace::BeatmapLevel* beatmapLevel, ::GlobalNamespace::OverrideEnvironmentSettings* overrideEnvironmentSettings,
    ::GlobalNamespace::ColorScheme* playerOverrideColorScheme, bool playerOverrideLightshowColors, ::GlobalNamespace::GameplayModifiers* gameplayModifiers,
    ::GlobalNamespace::PlayerSpecificSettings* playerSpecificSettings, ::GlobalNamespace::PracticeSettings* practiceSettings, ::GlobalNamespace::EnvironmentsListModel* environmentsListModel,
    ::GlobalNamespace::AudioClipAsyncLoader* audioClipAsyncLoader, ::GlobalNamespace::SettingsManager* settingsManager, ::GlobalNamespace::GameplayAdditionalInformation* gameplayAdditionalInformation,
    ::GlobalNamespace::BeatmapDataLoader* beatmapDataLoader, ::GlobalNamespace::BeatmapLevelsEntitlementModel* beatmapLevelsEntitlementModel, ::GlobalNamespace::BeatmapLevelsModel* beatmapLevelsModel,
    ::GlobalNamespace::IBeatmapLevelData* beatmapLevelData, ::System::Nullable_1<::GlobalNamespace::RecordingToolManager_SetupData> recordingToolData) {
  auto customBeatmapLevel = il2cpp_utils::try_cast<SongCore::SongLoader::CustomBeatmapLevel>(beatmapLevel);
  if (!customBeatmapLevel) {
    StandardLevelScenesTransitionSetupDataSO_Init(self, gameMode, beatmapKey, beatmapLevel, overrideEnvironmentSettings, playerOverrideColorScheme, playerOverrideLightshowColors, gameplayModifiers, playerSpecificSettings, practiceSettings, environmentsListModel, audioClipAsyncLoader, settingsManager, gameplayAdditionalInformation, beatmapDataLoader, beatmapLevelsEntitlementModel, beatmapLevelsModel, beatmapLevelData, recordingToolData);
    return;
  }

  // TODO: Fix environment override
  auto targetEnvironmentInfo = GlobalNamespace::StandardLevelScenesTransitionSetupDataSO::GetEnvironmentInfo(*beatmapKey, beatmapLevel, overrideEnvironmentSettings, environmentsListModel);
  SceneTransitionHelper::Patch(customBeatmapLevel.value(), *beatmapKey, targetEnvironmentInfo.Item2,
                               playerSpecificSettings);

    StandardLevelScenesTransitionSetupDataSO_Init(self, gameMode, beatmapKey, beatmapLevel, overrideEnvironmentSettings, playerOverrideColorScheme, playerOverrideLightshowColors, gameplayModifiers, playerSpecificSettings, practiceSettings, environmentsListModel, audioClipAsyncLoader, settingsManager, gameplayAdditionalInformation, beatmapDataLoader, beatmapLevelsEntitlementModel, beatmapLevelsModel, beatmapLevelData, recordingToolData);
}

void InstallStandardLevelScenesTransitionSetupDataSOHooks() {
  INSTALL_HOOK(NELogger::Logger, StandardLevelScenesTransitionSetupDataSO_Init);
}

NEInstallHooks(InstallStandardLevelScenesTransitionSetupDataSOHooks);