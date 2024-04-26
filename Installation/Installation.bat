@echo off

REM Set the name of the Conda environment
set env_name=pcgrl_env
set env_path=D:\Anaconda3\envs\pcgrl_env

ECHO Preparing Conda Environment...

REM Remove existing Conda environment if it exists
call conda env remove --name %env_name% --yes

REM Create a new Conda environment with specified Python version
call conda create --prefix %env_path% python=3.7.0 --yes

REM Activate the Conda environment
CALL conda activate %env_path%

REM Install CUDA Toolkit
call conda install -c conda-forge cudatoolkit=10.0 --yes

REM Uninstall existing TensorFlow packages if they are installed
call conda uninstall tensorflow tensorflow-estimator tensorboard --yes

REM Install specific versions of TensorFlow packages
call conda install tensorflow==1.15.0 tensorflow-estimator==1.15.1 tensorflow-gpu==1.15.0 tensorboard==1.15.0 --yes

REM Install other required packages with pip
call pip install stable-baselines==2.9.0
call pip install gym==0.14.0
call pip install tensorflow-gpu==1.15

REM Install OpenAI
call pip install openai

REM Install current directory as a package
call pip install -e .

REM Set environment variables
set CUDA_HOME=C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v10.0
set PATH=%CUDA_HOME%\bin;%CUDA_HOME%\libnvvp;%PATH%

ECHO Environment setup complete!
pause