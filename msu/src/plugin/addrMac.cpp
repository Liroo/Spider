
#include <iostream>
#include "plugin/addrMac.hpp"

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/types.hpp>

AddrMac::AddrMac() {
  name = std::string("ADDR_MAC");
}
AddrMac::~AddrMac() {}

bool AddrMac::test(std::string res) {
  return (res.compare(0, name.length(), name) == 0);
}

int AddrMac::exec(mongocxx::database db, Session * session, std::string msg) {
  std::string mac = msg.substr(msg.find(" ") + 1);
  mac.erase(mac.size() - 1);

  std::cout << "The client [" << session->getUniqueId() << "] is using : ";
  std::cout << "addr_mac [" << mac << "]" << std::endl;
  session->setMacAddress(mac);

  auto old_builder = bsoncxx::builder::stream::document{};
  bsoncxx::document::value old_doc = old_builder
    << "uniq_id" << boost::uuids::to_string(session->getUniqueId())
    << bsoncxx::builder::stream::finalize;

  auto new_builder = bsoncxx::builder::stream::document{};
  bsoncxx::document::value new_doc = new_builder
    << "$set" <<
    bsoncxx::builder::stream::open_document
      << "mac_addr" << session->getMacAddr()
    << bsoncxx::builder::stream::close_document
    << bsoncxx::builder::stream::finalize;

  mongocxx::collection coll = db["sessions"];
  coll.update_one(std::move(old_doc), std::move(new_doc));

  return (0);
}
