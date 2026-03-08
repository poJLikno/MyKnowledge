#ifndef TRY_CATCH_DIY_H_
#define TRY_CATCH_DIY_H_

#include <stdlib.h>
#include <setjmp.h>
#include <iostream>
#include <string>

class try_catch_diy_support
{
protected:
    try_catch_diy_support();

    try_catch_diy_support(const try_catch_diy_support &) = delete;
    try_catch_diy_support(try_catch_diy_support &&) = delete;

public:
    try_catch_diy_support *previous_obj = reinterpret_cast<try_catch_diy_support *>(~0);

    virtual ~try_catch_diy_support() noexcept;
};

class try_catch_block
{
public:
    jmp_buf jmp_buffer = {};
    try_catch_block *previous_block = nullptr;
    try_catch_diy_support *obj_list = nullptr;

    static try_catch_block *current_block;
    static std::string current_exception;

    try_catch_block();

    try_catch_block(const try_catch_block &) = delete;
    try_catch_block(try_catch_block &&) = delete;

    ~try_catch_block() noexcept;
};

void throw_diy(std::string exc_msg) noexcept;
void throw_diy() noexcept;

#define TRY_BLOCK do { \
    try_catch_block tc_block; \
    int error_state = setjmp(tc_block.jmp_buffer); \
    if (error_state == 0) {

#define CATCH_BLOCK } else

#define END_BLOCK \
    } while(false)

#define THROW_IN_BLOCK(exception) throw_diy(exception)
#define RETHROW_IN_BLOCK throw_diy()

#endif /* TRY_CATCH_DIY_H_ */
