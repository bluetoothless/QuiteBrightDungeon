@echo off

REM Set the Anaconda directory and virtual environment name
set python_dir_for_conda=C:\Python39
set conda_dir=D:\Anaconda3
set conda_env_name=CondaEnv

REM Set the Python directory and virtual environment name
set python_dir=C:\Python311
set venv_project_path=VirtualEnv

ECHO Installing Conda environment...

REM Check if Anaconda is installed
if not exist "%conda_dir%" (
    echo Anaconda is not installed at %conda_dir%. Please install it first.
    goto :eof
)

REM Check if Python is installed
if not exist "%python_dir%" (
    echo Installing python to %python_dir%
    .\python-3.9.1.exe /Include_test=0 TargetDir=%python_dir% /Include_debug=1
    if errorlevel 1 (
        echo Installation failed.
        exit /b 1
    ) else (
        echo Installation completed successfully.
    )
) else (
    echo Python is already installed at %python_dir%.
)

REM Check if the conda environment exists, if not, create it and install the required packages
call %conda_dir%\Scripts\conda info --envs | findstr /B /C:"%conda_env_name%"
if errorlevel 1 (
    echo Creating Anaconda environment
    call %conda_dir%\Scripts\conda create --name %conda_env_name% python=3.9 -y

  echo Activating the Anaconda environment
  call %conda_dir%\Scripts\conda activate %conda_env_name%

    echo Installing requirements
    call %conda_dir%\Scripts\conda install --file training_env_requirements.txt -y

    REM Installing PyTorch with CUDA 11.1 support (or closest available)
    call %conda_dir%\Scripts\conda install pytorch torchvision torchaudio cudatoolkit=11.1 -c pytorch -c conda-forge -y
  
  echo Deactivating the Anaconda environment
  call %conda_dir%\Scripts\conda deactivate
)

ECHO Installing virtual environment...

REM Check if Python is installed
if not exist "%python_dir%" (
    echo Installing python to %python_dir%
    .\python-3.11.1.exe /Include_test=0 TargetDir=%python_dir% /Include_debug=1
    if errorlevel 1 (
        echo Installation failed.
        exit /b 1
    ) else (
        echo Installation completed successfully.
    )
) else (
    echo Python is already installed at %python_dir%.
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