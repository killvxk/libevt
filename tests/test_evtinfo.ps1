# Info tool testing script
#
# Version: 20170910

$ExitSuccess = 0
$ExitFailure = 1
$ExitIgnore = 77

$InputGlob = "*"

$TestToolDirectory = ""

ForEach (${VSDirectory} in "msvscpp vs2008 vs2010 vs2012 vs2013 vs2015 vs2017" -split " ")
{
	ForEach (${VSConfiguration} in "Release VSDebug" -split " ")
	{
		$TestToolDirectory = "..\${VSDirectory}\${VSConfiguration}"

		If (Test-Path ${TestToolDirectory})
		{
			Break
		}
		ForEach (${VSPlatform} in "Win32 x64" -split " ")
		{
			$TestToolDirectory = "..\${VSDirectory}\${VSConfiguration}\${VSPlatform}"

			If (Test-Path ${TestToolDirectory})
			{
				Break
			}
		}
	}
}
If (-Not (Test-Path ${TestToolDirectory}))
{
	Write-Host "Missing test tool directory." -foreground Red

	Exit ${ExitFailure}
}

$TestExecutable = "${TestToolDirectory}\evtinfo.exe"

If (-Not (Test-Path -Path "input"))
{
	Exit ${ExitSuccess}
}

Get-ChildItem -Path "input\${InputGlob}" | Foreach-Object
{
	Invoke-Expression ${TestExecutable} $_

	If (${LastExitCode} -ne ${ExitSuccess})
	{
		Break
	}
}

Exit ${LastExitCode}

