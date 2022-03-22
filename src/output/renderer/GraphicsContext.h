#ifndef UNKNOWN_GRAPHICSCONTEXT_H
#define UNKNOWN_GRAPHICSCONTEXT_H

class GraphicsContext {
public:
    GraphicsContext() = default;
    virtual ~GraphicsContext() = default;
    virtual void Initialize() = 0;
};

#endif