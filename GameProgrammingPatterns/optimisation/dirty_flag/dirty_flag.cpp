class Transform {
public:
    static Transform origin();
    Transform combine(Transform& other);
};

class GraphNode {
public:
    GraphNode(Mesh* mesh)
    : mesh_(mesh), local_(Transform::origin()), dirty_(true) {}

    void setTransform(Transform local);
    void render(Transform parentWorld, bool dirty);

private:
    Transform local_;
    Transform world_;
    bool dirty_;
    Mesh* mesh_;
    GraphNode* children_[MAX_CHILDREN];
    int numChildren_;
};

void GraphNode::setTransform(Transform local) {
    local_ = local;
    dirty_ = true;
}

void GraphNode::render(Transform parentWorld, bool dirty)
{
    dirty |= dirty_;
    if (dirty) {
        world_ = local_.combine(parentWorld);
        dirty_ = false;
    }
    
    if (mesh_) renderMesh(mesh_, world_);
    
    for (int i = 0; i < numChildren_; i++) {
        children_[i]->render(world_, dirty);
    }
}

int main() {
    GraphNode* graph_ = new GraphNode(nullptr);
    // Add children to root graph node...
    graph_->render(Transform::origin(), true);
}