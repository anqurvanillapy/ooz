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
} err_t;
