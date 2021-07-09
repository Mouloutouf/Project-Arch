#include "Element.h"

Element::Element()
{
}

Element::~Element()
{
}

Transform2D* Element::GetTransform()
{
    return &transform;
}

Element* Element::GetParent()
{
    return parent;
}

Element* Element::GetFirstChild()
{
    if (children.size() == 0) return nullptr;
    return children[0];
}

vector<Element*> Element::GetChildren()
{
    return children;
}
