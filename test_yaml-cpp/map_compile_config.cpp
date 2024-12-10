#include "map_compile_config.h"

namespace map_compile {

bool MapCompileConfig::parseConfig(const std::string &config_file_path) {
  if (access(config_file_path.c_str(), 0) == -1) {
    std::cout << "[config][error]: file " << config_file_path << " not exist!"
              << std::endl;
    return false;
  }

  YAML::Node root = YAML::LoadFile(config_file_path);
  YAML::Node dbnode = root["database"];
  if (!dbnode.IsMap()) {
    std::cout << "[config][error]: \"database\" field syntax invalid!!!!"
              << std::endl;
    return false;
  }

  m_dbname = dbnode["db"].as<std::string>();
  m_ip = dbnode["ip"].as<std::string>();
  m_port = dbnode["port"].as<std::string>();
  m_user = dbnode["user"].as<std::string>();
  m_password = dbnode["password"].as<std::string>();
  m_outputName = dbnode["output_name"].as<std::string>();
  m_debug = dbnode["debug"].as<bool>();

  return true;
}

}  // namespace map_compile