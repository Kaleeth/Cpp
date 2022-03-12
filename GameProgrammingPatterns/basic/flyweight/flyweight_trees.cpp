// Example of basic tree class
// Not good idea when having a forest of 'em

class Tree { 
private:
    Mesh mesh_;
    Texture bark_;
    Texture leaves_;
    Vector position_;
    double height_;
    double thickness_;
    Color barkTint_;
    Color leafTint_;
};

// extracting common elements -->

class TreeModel { 
private:
    Mesh mesh_;
    Texture bark_;
    Texture leaves_;
};

class Tree { 
private:
    TreeModel* model_;
    Vector position_;
    double height_;
    double thickness_;
    Color barkTint_;
    Color leafTint_;
};