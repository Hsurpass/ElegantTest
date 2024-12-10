#pragma once

#include <unistd.h>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <string>

namespace map_compile {

class MapCompileConfig {
 public:
  static MapCompileConfig *GetInstance() {
    static MapCompileConfig instance;
    return &instance;
  }

  bool parseConfig(const std::string &config_file_path);

  std::string &dbname() { return m_dbname; }
  std::string &ip() { return m_ip; }
  std::string &port() { return m_port; }
  std::string &user() { return m_user; }
  std::string &password() { return m_password; }
  std::string &outputName() { return m_outputName; }
  std::string &debug() { return m_debug; }

 private:
  std::string m_dbname;
  std::string m_ip;
  std::string m_port;
  std::string m_user;
  std::string m_password;
  std::string m_outputName;
  std::string m_debug;
};

}  // namespace map_compile