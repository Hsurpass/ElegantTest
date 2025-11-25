#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <pqxx/pqxx>

int main() {
    // 启动 SSH 隧道
    std::string ssh_cmd = "sshpass -p 'sshpassword' ssh -L 5433:10.35.1.44:5432 "
                         "-p 22 sshuser@ip -N -f -o StrictHostKeyChecking=no";
    
    std::cout << "Starting SSH tunnel..." << std::endl;
    system(ssh_cmd.c_str());
    std::this_thread::sleep_for(std::chrono::seconds(3));

    try {
        // 连接数据库
        std::string conn_str = "host=localhost port=5433 dbname=remote_db "
                              "user=remote_db_user password=remote_db_password";
        
        pqxx::connection conn(conn_str);
        std::cout << "Connected to database successfully!" << std::endl;
        
        // 执行查询
        pqxx::work txn(conn);
        pqxx::result result = txn.exec("SELECT version();");
        std::cout << "PostgreSQL: " << result[0][0].as<std::string>() << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // 清理
    system("pkill -f 'ssh -L 5433'");
    std::cout << "SSH tunnel closed." << std::endl;
    return 0;
}