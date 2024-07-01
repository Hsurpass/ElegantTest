import sys
import subprocess

script = "pass_cmd_arg.sh"

if __name__ == '__main__':
    # if len(sys.argv) < 2:  
    #     print("Usage: python batch_bad_case.py 1 or 0")
    #     sys.exit(1)
    arg1 = sys.argv[1]
    arg2 = sys.argv[2]
    arg3 = sys.argv[3]
    arg4 = sys.argv[4]
    arg5 = sys.argv[5]

    print(type(arg4))

    result = subprocess.run(['bash', script, arg1, arg2, arg3, str(arg4), arg5], check=True, stdout=subprocess.PIPE, universal_newlines=True)
    print(result.stdout)
