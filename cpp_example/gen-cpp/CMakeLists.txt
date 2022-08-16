set(thrift_IF_src
    ${CMAKE_CURRENT_SOURCE_DIR}/myfirst_types.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MyFirstService.cpp
    PARENT_SCOPE
)

set(thrift_IF_hdr 
    ${CMAKE_CURRENT_SOURCE_DIR}/myfirst_types.h
    ${CMAKE_CURRENT_SOURCE_DIR}/MyFirstService.h
    PARENT_SCOPE
)

set(thrift_IF_tmpl
    ${CMAKE_CURRENT_SOURCE_DIR}/MyFirstService.tcc
    ${CMAKE_CURRENT_SOURCE_DIR}/myfirst_types.tcc
    PARENT_SCOPE
)