// sudo apt-get update
// sudo apt-get install g++ cmake libpqxx-dev libpq-dev sshpass

#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <pqxx/pqxx>

class SSHTunnel {
private:
    std::string m_ssh_host;
    std::string m_ssh_user;
    std::string m_ssh_password;
    int m_ssh_port;
    int m_local_port;
    int m_remote_port;
    std::string m_remote_host;
public:
    SSHTunnel(const std::string& ssh_host, const std::string& ssh_user, const std::string& ssh_password,
              int ssh_port = 22, int local_port = 5433, 
              int remote_port = 5432, const std::string& remote_host = "localhost")
        : m_ssh_host(ssh_host), m_ssh_user(ssh_user), m_ssh_password(ssh_password), m_ssh_port(ssh_port),
          m_local_port(local_port), m_remote_port(remote_port), m_remote_host(remote_host) {
            // start();
        }

    ~SSHTunnel() {
        stop();
    }

    bool start() {
        // 使用 sshpass 来处理密码认证
        std::string command = "sshpass -p '" + m_ssh_password + "' ssh -L " + 
                             std::to_string(m_local_port) + ":" + m_remote_host + ":" + 
                             std::to_string(m_remote_port) + " -p " + std::to_string(m_ssh_port) + 
                             " " + m_ssh_user + "@" + m_ssh_host + 
                             " -N -f -o StrictHostKeyChecking=no";
        
        std::cout << "Starting SSH tunnel..." << std::endl;
        std::cout << "Command: ssh -L " << m_local_port << ":" << m_remote_host << ":" << m_remote_port 
                  << " " << m_ssh_user << "@" << m_ssh_host << ":" << m_ssh_port << std::endl;
        
        int result = std::system(command.c_str());
        if (result != 0) {
            std::cerr << "Failed to start SSH tunnel. Error code: " << result << std::endl;
            std::cerr << "Please make sure sshpass is installed: sudo apt-get install sshpass" << std::endl;
            return false;
        }
        
        // 等待隧道建立
        std::cout << "Waiting for SSH tunnel to establish..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
        return true;
    }

    void stop() {
        std::string command = "pkill -f \"ssh -L " + std::to_string(m_local_port) + "\"";
        int result = std::system(command.c_str());
        if (result == 0) {
            std::cout << "SSH tunnel stopped successfully" << std::endl;
        }
    }

    int getLocalPort() const {
        return m_local_port;
    }
};

class PostgreSQLConnection {
private:
    std::string connection_string;

public:
    PostgreSQLConnection(const std::string& host, int port, 
                        const std::string& dbname, const std::string& user, 
                        const std::string& password) {
        connection_string = "host=" + host + " port=" + std::to_string(port) + 
                           " dbname=" + dbname + " user=" + user + 
                           " password=" + password + " connect_timeout=10";
        
        std::cout << "Database connection string: " << std::endl;
        std::cout << "  Host: " << host << ":" << port << std::endl;
        std::cout << "  Database: " << dbname << std::endl;
        std::cout << "  User: " << user << std::endl;
    }

    bool testConnection() {
        try {
            std::cout << "Testing database connection..." << std::endl;
            pqxx::connection conn(connection_string);
            
            if (conn.is_open()) {
                std::cout << "✓ Connected to PostgreSQL successfully!" << std::endl;
                
                // 执行简单查询测试
                pqxx::work txn(conn);
                pqxx::result result = txn.exec("SELECT version();");
                
                for (const auto& row : result) {
                    std::cout << "✓ PostgreSQL version: " << row[0].as<std::string>() << std::endl;
                }
                
                // 获取当前数据库信息
                result = txn.exec("SELECT current_database(), current_user, current_timestamp;");
                for (const auto& row : result) {
                    std::cout << "✓ Current database: " << row[0].as<std::string>() << std::endl;
                    std::cout << "✓ Current user: " << row[1].as<std::string>() << std::endl;
                    std::cout << "✓ Current time: " << row[2].as<std::string>() << std::endl;
                }
                
                txn.commit();
                conn.disconnect();
                // conn.close();
                return true;
            } else {
                std::cerr << "✗ Database connection failed: Connection not open" << std::endl;
                return false;
            }
        } catch (const std::exception& e) {
            std::cerr << "✗ Connection failed: " << e.what() << std::endl;
            return false;
        }
    }

    void executeQuery(const std::string& query) {
        try {
            pqxx::connection conn(connection_string);
            pqxx::work txn(conn);
            
            std::cout << "Executing query: " << query << std::endl;
            pqxx::result result = txn.exec(query);
            
            if (result.empty()) {
                std::cout << "Query executed successfully, no results returned." << std::endl;
            } else {
                std::cout << "Query results (" << result.size() << " rows):" << std::endl;
                
                // 打印列名
                if (!result.empty()) {
                    std::cout << "Columns: ";
                    for (pqxx::row_size_type i = 0; i < result.columns(); ++i) {
                        std::cout << result.column_name(i) << "\t";
                    }
                    std::cout << std::endl;
                }
                
                // 打印数据
                for (const auto& row : result) {
                    for (const auto& field : row) {
                        std::cout << field.c_str() << "\t";
                    }
                    std::cout << std::endl;
                }
            }
            
            txn.commit();
            conn.disconnect();
            
        } catch (const std::exception& e) {
            std::cerr << "Query execution failed: " << e.what() << std::endl;
        }
    }

    void listTables() {
        try {
            pqxx::connection conn(connection_string);
            pqxx::work txn(conn);
            
            std::string query = 
                "SELECT table_name FROM information_schema.tables "
                "WHERE table_schema = 'public' ORDER BY table_name;";
            
            std::cout << "Listing database tables:" << std::endl;
            pqxx::result result = txn.exec(query);
            
            if (result.empty()) {
                std::cout << "No tables found in the database." << std::endl;
            } else {
                std::cout << "Found " << result.size() << " tables:" << std::endl;
                for (const auto& row : result) {
                    std::cout << "  - " << row[0].as<std::string>() << std::endl;
                }
            }
            
            txn.commit();
            conn.disconnect();
            
        } catch (const std::exception& e) {
            std::cerr << "Failed to list tables: " << e.what() << std::endl;
        }
    }
};

int main() {
    std::cout << "=== PostgreSQL SSH Tunnel Connection ===" << std::endl;
    
    // SSH 隧道配置
    std::string ssh_host = "ssh_host";
    std::string ssh_user = "ssh_user";
    std::string ssh_password = "ssh_password";
    int ssh_port = 22;
    int local_port = 5433;      // 本地隧道端口
    int remote_port = 5432;     // 远程 PostgreSQL 端口
    std::string remote_db_host = "remote_db_host"; // 远程数据库IP
    
    // PostgreSQL 配置
    std::string db_host = "localhost"; // 通过本地隧道连接
    int db_port = local_port;
    std::string db_name = "remote_db_name";
    std::string db_user = "remote_db_user";
    std::string db_password = "remote_db_password";

    // 创建 SSH 隧道
    SSHTunnel tunnel(ssh_host, ssh_user, ssh_password, ssh_port, 
                    local_port, remote_port, remote_db_host);
    
    std::cout << "\nStep 1: Setting up SSH tunnel..." << std::endl;
    if (!tunnel.start()) {
        std::cerr << "Failed to establish SSH tunnel. Exiting." << std::endl;
        return -1;
    }
    std::cout << "✓ SSH tunnel established on localhost:" << local_port << std::endl;

    // 创建数据库连接
    std::cout << "\nStep 2: Connecting to PostgreSQL..." << std::endl;
    PostgreSQLConnection db_conn(db_host, db_port, db_name, db_user, db_password);
    
    // 测试连接
    if (db_conn.testConnection()) {
        std::cout << "\nStep 3: Database operations..." << std::endl;
        
        // 列出所有表
        // db_conn.listTables();
        
        // 执行示例查询
        // std::cout << "\nStep 4: Executing sample queries..." << std::endl;
        // db_conn.executeQuery("SELECT current_timestamp;");
        
        // 可以在这里执行更多自定义查询
        // db_conn.executeQuery("SELECT * FROM your_table_name LIMIT 5;");
        
    } else {
        std::cerr << "\n✗ Failed to connect to database. Please check your credentials." << std::endl;
    }

    // 关闭隧道
    std::cout << "\nStep 5: Cleaning up..." << std::endl;
    tunnel.stop();
    std::cout << "✓ Program completed successfully!" << std::endl;

    return 0;
}