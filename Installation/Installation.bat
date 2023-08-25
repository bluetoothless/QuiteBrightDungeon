@echo off

REM Set the Python directory and virtual environment name
set python_dir=C:\Python311
set venv_project_path=VirtualEnv

ECHO Installing...

REM Check if Python is installed
if not exist "%python_dir%" (
    echo Installing python to %python_dir%
    .\python-3.11.1.exe /passive Include_test=0 TargetDir=%python_dir% /Include_debug=1
    echo done
)

REM Check if virtualenv is installed
if not exist "%python_dir%\Scripts\virtualenv.exe" (
    echo Installing virtualenv
    %python_dir%\Scripts\pip -q install virtualenv --disable-pip-version-check
)

REM Check if the virtual environment exists, if not, create it and install the required packages
if not exist "%venv_project_path%\Scripts\python.exe" (
    echo Creating python virtual environment
    %python_dir%\python -m venv %venv_project_path%

	echo Upgrading pip in the virtual environment
	%venv_project_path%\Scripts\python.exe -m pip install --upgrade pip --disable-pip-version-check
    REM %venv_project_path%\Scripts\pip install --upgrade pip --disable-pip-version-check
	
    echo Installing requirements
    %venv_project_path%\Scripts\pip install --disable-pip-version-check -q -r requirements.txt
)

echo on