#include <stdio.h>

#include "ast/ast.h"
#include "filegen/driver.h"
#include "filegen/genmacros.h"

#include "filegen/gen-enum.h"
#include "filegen/gen-util.h"

static int indent = 0;

void gen_enum(Config *config, FILE *fp, Enum *arg_enum) {
    char *arg_enumupr = strupr(arg_enum->id);
    out_comment("Enum %s", arg_enum->id);
    out_enum("%s", arg_enumupr);
    out_enum_field("%s_NULL", arg_enum->prefix);
    for (int i = 0; i < array_size(arg_enum->values); i++) {
        char *id = (char *)array_get(arg_enum->values, i);
        out_enum_field("%s_%s", arg_enum->prefix, id);
    }
    out_enum_end("%s", arg_enum->id);
    free(arg_enumupr);
}

void gen_nodetype_enum(Config *config, FILE *fp) {
    out_comment("Enum NodeType");
    out_enum("NODETYPE");
    out_enum_field("NT_NULL");
    out_comment("Nodes");
    for (int i = 0; i < array_size(config->nodes); ++i) {
        Node *node = (Node *)array_get(config->nodes, i);
        char *nodelwr = strlwr(node->id);
        out_enum_field("NT_%s", nodelwr);
        free(nodelwr);
    }
    out_comment("Nodesets");
    for (int i = 0; i < array_size(config->nodesets); ++i) {
        Nodeset *nodeset = (Nodeset *)array_get(config->nodesets, i);
        char *nodesetlwr = strlwr(nodeset->id);
        out_enum_field("NT_%s", nodesetlwr);
        free(nodesetlwr);
    }
    out_enum_end("NodeType");
}

void gen_traversal_enum(Config *config, FILE *fp) {
    out_enum("TRAVERSALS");
    out_comment("Traversals");
    out_enum_field("TRAV_NULL");
    for (int i = 0; i < array_size(config->traversals); ++i) {
        Traversal *trav = (Traversal *)array_get(config->traversals, i);
        char *travlwr = strlwr(trav->id);
        out_enum_field("TRAV_%s", travlwr);
        free(travlwr);
    }
    out_enum_field("TRAV_free");
    out_enum_field("TRAV_copy");
    out_enum_end("TraversalType");
}

void gen_enum_header(Config *config, FILE *fp) {
    out("#ifndef _CCN_ENUM_H_\n");
    out("#define _CCN_ENUM_H_\n\n");
    gen_nodetype_enum(config, fp);
    gen_traversal_enum(config, fp);
    for (int i = 0; i < array_size(config->enums); ++i) {
        Enum *arg_enum = (Enum *)array_get(config->enums, i);
        gen_enum(config, fp, arg_enum);
    }
    out("#endif /* _CCN_ENUM_H_ */\n");
}

void gen_enum_src(Config *config, FILE *fp) {}
