#include "screen_config.h"
#include "../3rd_party/pugi_xml/pugixml.hpp"

const std::string ScreenConfig::XML_TYPE_UNKNOWN = "UNKNOWN";
const std::string ScreenConfig::XML_TYPE_IMAGE = "IMAGE";
const std::string ScreenConfig::XML_TYPE_AUDIO = "AUDIO";
const std::string ScreenConfig::XML_TYPE_VIDEO = "VIDEO";
const std::string ScreenConfig::XML_TYPE_OTHER = "OTHER";


void ScreenConfig::load_outputs_xml(char *xml_filename) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(xml_filename);
    if (result.status!=pugi::status_ok)
        return;
    pugi::xml_node root = doc.child("outputs");
    for (pugi::xml_node node = root.child("output"); node; node = node.next_sibling("output")) {
        Output output;
        output.enabled = true;
        output.filename = node.attribute("filename").value();
        std::string type = node.attribute("type").value();
        if (type == XML_TYPE_UNKNOWN) output.type = TYPE_UNKNOWN;
        if (type == XML_TYPE_IMAGE) output.type = TYPE_IMAGE;
        if (type == XML_TYPE_AUDIO) output.type = TYPE_AUDIO;
        if (type == XML_TYPE_VIDEO) output.type = TYPE_VIDEO;
        if (type == XML_TYPE_OTHER) output.type = TYPE_OTHER;
        outputs.push_back(output);
    }

}
