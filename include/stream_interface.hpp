#pragma once

template<typename T>
class StreamInterface {
    virtual T next() = 0;
    virtual void reset() = 0;
};
