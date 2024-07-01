#!/usr/bin/python
import subprocess  
  
def uninstall_requirements(requirements_file):  
    with open(requirements_file, 'r') as f:  
        for line in f:  
            # 去除可能存在的注释和空行  
            line = line.strip()  
            if line and not line.startswith('#'):  
                # 使用 pip 卸载依赖  
                subprocess.run(['pip', 'uninstall', '-y', line.split('=')[0]], check=True)  
  
if __name__ == "__main__":  
    uninstall_requirements('requirements.txt')