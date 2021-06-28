//
// Created by henryj on 28/6/2021.
//

#pragma once

#define OFFSET_STRUCT(name, members) \
    union name {                    \
        members                     \
    }
#define OFFSET_FIELD(name, offset)        \
    struct __attribute__((__packed__)) { \
        char pad_##offset[offset];       \
        name;                            \
    }
#define OF OFFSET_FIELD
