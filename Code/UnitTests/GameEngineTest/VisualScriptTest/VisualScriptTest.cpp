#include <GameEngineTest/GameEngineTestPCH.h>

#include "VisualScriptTest.h"
#include <Core/WorldSerializer/WorldReader.h>
#include <Foundation/IO/FileSystem/FileReader.h>

static ezGameEngineTestVisualScript s_GameEngineTestAnimations;

const char* ezGameEngineTestVisualScript::GetTestName() const
{
  return "VisualScript Tests";
}

ezGameEngineTestApplication* ezGameEngineTestVisualScript::CreateApplication()
{
  m_pOwnApplication = EZ_DEFAULT_NEW(ezGameEngineTestApplication, "VisualScript");
  return m_pOwnApplication;
}

void ezGameEngineTestVisualScript::SetupSubTests()
{
  AddSubTest("Variables", SubTests::Variables);
  AddSubTest("Coroutines", SubTests::Coroutines);
  AddSubTest("Messages", SubTests::Messages);
  AddSubTest("EnumsAndSwitch", SubTests::EnumsAndSwitch);
}

ezResult ezGameEngineTestVisualScript::InitializeSubTest(ezInt32 iIdentifier)
{
  EZ_SUCCEED_OR_RETURN(SUPER::InitializeSubTest(iIdentifier));

  m_iFrame = -1;
  m_uiImgCompIdx = 0;
  m_ImgCompFrames.Clear();

  if (iIdentifier == SubTests::Variables)
  {
    m_ImgCompFrames.PushBack(1);

    EZ_SUCCEED_OR_RETURN(m_pOwnApplication->LoadScene("VisualScript/AssetCache/Common/Scenes/Variables.ezObjectGraph"));
    return EZ_SUCCESS;
  }
  else if (iIdentifier == SubTests::Coroutines)
  {
    m_ImgCompFrames.PushBack(1);
    m_ImgCompFrames.PushBack(4);
    m_ImgCompFrames.PushBack(10);
    m_ImgCompFrames.PushBack(17);

    EZ_SUCCEED_OR_RETURN(m_pOwnApplication->LoadScene("VisualScript/AssetCache/Common/Scenes/Coroutines.ezObjectGraph"));
    return EZ_SUCCESS;
  }
  else if (iIdentifier == SubTests::Messages)
  {
    m_ImgCompFrames.PushBack(1);
    m_ImgCompFrames.PushBack(4);

    EZ_SUCCEED_OR_RETURN(m_pOwnApplication->LoadScene("VisualScript/AssetCache/Common/Scenes/Messages.ezObjectGraph"));
    return EZ_SUCCESS;
  }
  else if (iIdentifier == SubTests::EnumsAndSwitch)
  {
    m_ImgCompFrames.PushBack(1);
    m_ImgCompFrames.PushBack(2);
    m_ImgCompFrames.PushBack(3);
    m_ImgCompFrames.PushBack(6);

    EZ_SUCCEED_OR_RETURN(m_pOwnApplication->LoadScene("VisualScript/AssetCache/Common/Scenes/EnumsAndSwitch.ezObjectGraph"));
    return EZ_SUCCESS;
  }

  return EZ_FAILURE;
}

ezTestAppRun ezGameEngineTestVisualScript::RunSubTest(ezInt32 iIdentifier, ezUInt32 uiInvocationCount)
{
  const bool bVulkan = ezGameApplication::GetActiveRenderer().IsEqual_NoCase("Vulkan");
  ++m_iFrame;

  if (m_pOwnApplication->Run() == ezApplication::Execution::Quit)
    return ezTestAppRun::Quit;

  if (m_ImgCompFrames[m_uiImgCompIdx] == m_iFrame)
  {
    EZ_TEST_IMAGE(m_uiImgCompIdx, bVulkan ? 300 : 250);
    ++m_uiImgCompIdx;

    if (m_uiImgCompIdx >= m_ImgCompFrames.GetCount())
    {
      return ezTestAppRun::Quit;
    }
  }

  return ezTestAppRun::Continue;
}
