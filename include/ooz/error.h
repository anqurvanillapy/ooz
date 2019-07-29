/**
 * @file error.h
 * Error types and values
 */

#pragma once

typedef enum err {
    OK,
    ErrNullPointer,
    ErrFilePath,
    ErrOpenFile,
    ErrNoMem,
} err_t;
