#include "try_catch_diy.h"

try_catch_block *try_catch_block::current_block = nullptr;
std::string try_catch_block::current_exception;

/* try_catch_diy_support */
try_catch_diy_support::try_catch_diy_support()
{
    if (try_catch_block::current_block != nullptr)
    {
        previous_obj = try_catch_block::current_block->obj_list;
        try_catch_block::current_block->obj_list = this;
    }    
}

try_catch_diy_support::~try_catch_diy_support() noexcept
{
    if (try_catch_block::current_block != nullptr && previous_obj != reinterpret_cast<try_catch_diy_support *>(~0))
    {
        try_catch_block::current_block->obj_list = previous_obj;
        previous_obj = reinterpret_cast<try_catch_diy_support *>(~0);
    }
}

/* try_catch_block */
try_catch_block::try_catch_block()
{
    previous_block = try_catch_block::current_block;
    try_catch_block::current_block = this;
}

try_catch_block::~try_catch_block() noexcept
{
    try_catch_block::current_block = previous_block;

    try_catch_block::current_exception = std::string();
}

/* throw_diy */
void throw_diy(std::string exception) noexcept
{
    if (try_catch_block::current_block == nullptr)
    {
        std::cerr << "* DIY Throw unhandled exception!\n";
        std::abort();
    }

    while (try_catch_block::current_block->obj_list)
    {
        try_catch_block::current_block->obj_list->~try_catch_diy_support();
    }

    try_catch_block::current_exception = std::move(exception);

    try_catch_block *tmp = try_catch_block::current_block;
    try_catch_block::current_block = tmp->previous_block;
    longjmp(tmp->jmp_buffer, 1);
}

void throw_diy() noexcept
{
    if (try_catch_block::current_block == nullptr)
    {
        std::cerr << "* DIY Throw unhandled exception!\n";
        std::abort();
    }

    if (try_catch_block::current_exception.length() == 0)
    {
        std::cerr << "* DIY No active exception for rethrow!\n";
        std::abort();
    }

    while (try_catch_block::current_block->obj_list)
    {
        try_catch_block::current_block->obj_list->~try_catch_diy_support();
    }

    try_catch_block *tmp = try_catch_block::current_block;
    try_catch_block::current_block = tmp->previous_block;
    longjmp(tmp->jmp_buffer, 1);
}
