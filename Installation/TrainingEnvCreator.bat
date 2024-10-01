@echo off

REM Set the Anaconda directory and virtual environment name
set conda_dir=D:\Anaconda3
set conda_env_name=CondaEnv

ECHO Installing...

REM Check if Anaconda is installed
if not exist "%conda_dir%" (
    echo Anaconda is not installed at %conda_dir%. Please install it first.
    goto :eof
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
)

echo on