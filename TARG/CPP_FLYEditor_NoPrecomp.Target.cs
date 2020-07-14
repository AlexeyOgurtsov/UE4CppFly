// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class CPP_FLYEditorTarget : TargetRules
{
	public CPP_FLYEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		ExtraModuleNames.AddRange( new string[] { "CPP_FLY" } );

		bUseUnityBuild = false;
		bUsePCHFiles = false;
	}
}
