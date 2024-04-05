#include <rt/groups/bvh.h>

namespace rt {

bool sortByX(Primitive* p1, Primitive* p2);
bool sortByY(Primitive* p1, Primitive* p2);
bool sortByZ(Primitive* p1, Primitive* p2);

BVH::BVH()
{
    //nothing
}

void BVH::rebuildIndex() {
    SerializedNode *root = new SerializedNode();
    root->isLeaf = true;
    for (const auto& p : this->primitives){
        root->primitives.push_back(p);
        root->bbox.extend(p->getBounds());
    }
    this->root = root;
    this->nodes.push_back(root);
    split(root);
}

BBox BVH::getBounds() const {
    return this->root->bbox;
}

Intersection BVH::intersect(const Ray& ray, float tmin, float tmax) const {
    return checkForIntersections(ray, this->root, tmin, tmax);
}

void BVH::add(Primitive* p) {
    this->primitives.push_back(p);
}

void BVH::setMaterial(Material* m) {
    for(auto primitive : this->primitives){
        primitive->setMaterial(m);
    }
}

void BVH::setCoordMapper(CoordMapper* cm) {
    /* TODO */ NOT_IMPLEMENTED;
}

void BVH::serialize(BVH::Output& output) {
    // To implement this function:
    // - Call output.setNodeCount() with the number of nodes in the BVH
    /* TODO */
    // - Set the root node index using output.setRootId()
    /* TODO */
    // - Write each and every one of the BVH nodes to the output using output.writeNode()
    /* TODO */ NOT_IMPLEMENTED;
}
void BVH::deserialize(BVH::Input& input) {
    // To implement this function:
    // - Allocate and initialize input.getNodeCount() nodes
    /* TODO */
    // - Fill your nodes with input.readNode(index)
    /* TODO */
    // - Use the node at index input.getRootId() as the root node
    /* TODO */ NOT_IMPLEMENTED;
}

void BVH::split(SerializedNode *node){
    if(node->primitives.size() <= 3){
        return;
    }
    float x_len = node->bbox.max.x - node->bbox.min.x;
    float y_len = node->bbox.max.y - node->bbox.min.y;
    float z_len = node->bbox.max.z - node->bbox.min.z;

    node->isLeaf = false;

    SerializedNode *child_left = new SerializedNode();
    SerializedNode *child_right = new SerializedNode();

    if(x_len >= y_len && x_len >= z_len){
        sort(node->primitives.begin(), node->primitives.end(), sortByX);
    }else if(y_len >= x_len && y_len >= z_len){
        sort(node->primitives.begin(), node->primitives.end(), sortByY);
    }else{
        sort(node->primitives.begin(), node->primitives.end(), sortByZ);
    }

    child_left->bbox = BBox::empty();
    child_right->bbox = BBox::empty();
    size_t count = 0;

    for(const auto& p : node->primitives){
        if(count < node->primitives.size()/2){
            child_left->bbox.extend(p->getBounds());
            child_left->primitives.push_back(p);
        }else{
            child_right->bbox.extend(p->getBounds());
            child_right->primitives.push_back(p);
        }
        count++;
    }   

    child_left->isLeaf = true;
    child_right->isLeaf = true;
    this->nodes.push_back(child_left);
    this->nodes.push_back(child_right);
    node->leftChildId = this->nodes.size()-2;
    node->rightChildId = this->nodes.size()-1;
    split(child_left);
    split(child_right);
}


Intersection BVH::checkForIntersections(Ray ray, SerializedNode *node, float tmin, float tmax) const{
    std::pair<float, float> t = node->bbox.intersect(ray);
    if(t.first > t.second ||  t.second <= 0){
        return Intersection::failure();
    }
    if(node->isLeaf){
        Intersection min = Intersection::failure();
        for(auto const& p : node->primitives){
            Intersection i = p->intersect(ray, tmin, tmax);
            if(i) {
                min = i;
                tmax = i.distance;
            }
        }
        return min;
    }else{
        Intersection li = checkForIntersections(ray, this->nodes[node->leftChildId], tmin, tmax);
        if(li) tmax = li.distance;
        Intersection lr = checkForIntersections(ray, this->nodes[node->rightChildId], tmin, tmax);
        if(li && lr) return li.distance < lr.distance ? li : lr;
        if(lr) return lr;
        if(li) return li;
        return Intersection::failure();
    }
}

// Point BVH::getCenter() const{
//     return Point();
// }

// bool sortByX(Primitive* p1, Primitive* p2){
//     return p1->getCenter().x < p2->getCenter().x;
// }
// bool sortByY(Primitive* p1, Primitive* p2){
//     return p1->getCenter().y < p2->getCenter().y;
// }
// bool sortByZ(Primitive* p1, Primitive* p2){
//     return p1->getCenter().z < p2->getCenter().z;
// }

bool sortByX(Primitive* p1, Primitive* p2){
    return p1->getBounds().getCenter().x < p2->getBounds().getCenter().x;
}
bool sortByY(Primitive* p1, Primitive* p2){
    return p1->getBounds().getCenter().y < p2->getBounds().getCenter().y;
}
bool sortByZ(Primitive* p1, Primitive* p2){
    return p1->getBounds().getCenter().z < p2->getBounds().getCenter().z;
}

}