#include <core/assert.h>
#include <core/scalar.h>
#include <core/image.h>
#include <rt/world.h>
#include <rt/renderer.h>
#include <rt/loaders/obj.h>
#include <rt/groups/bvh.h>
#include <rt/groups/simplegroup.h>
#include <rt/cameras/perspective.h>
#include <rt/integrators/recraytrace.h>

#include <rt/textures/constant.h>
#include <rt/textures/imagetex.h>
#include <rt/textures/perlin.h>

#include <rt/materials/lambertian.h>
#include <rt/materials/phong.h>
#include <rt/materials/flatmaterial.h>
#include <rt/materials/conductor.h>
#include <rt/materials/fuzzyconductor.h>
#include <rt/materials/dielectric.h>

#include <rt/lights/pointlight.h>
#include <rt/lights/arealight.h>

#include <rt/solids/quad.h>

using namespace rt;

BVH* getScene(std::string name, Material* material){
    BVH* scene = new BVH();
    loadOBJ(scene, "models/", name);
    scene->setMaterial(material);
    scene->rebuildIndex();
    return scene;
}

void a_rendering_competition() {
    Image img(3840, 2400);
    World world;
    SimpleGroup* scene = new SimpleGroup();

    //Keyboard
    Texture* black = new ConstantTexture(RGBColor::rep(0));
    Material* blackLambertian = new LambertianMaterial(black, black);
    Material* whiteLambertian = new LambertianMaterial(black, new ConstantTexture(RGBColor::rep(1)));

    Material* metailic = new ConductorMaterial(2.485, 3.433);
    Material* glass = new DielectricMaterial(2.0f);
    Material* glass_2 = new DielectricMaterial(1.55f);
    Material* mirror = new ConductorMaterial(0.177, 3.638);

    // //Keyboard
    Material* keyboardCaseMaterial = new LambertianMaterial(black, new ConstantTexture(RGBColor(30,30,30)/255));
    Material* keyboardBlueButtonsMaterial = new LambertianMaterial(black, new ConstantTexture(RGBColor(0,93,255)/255));
    Material* keyboardRedButtonsMaterial = new LambertianMaterial(black, new ConstantTexture(RGBColor(255,0,0)/255));

    // //Pot 
    Material* plantPotMaterial = new LambertianMaterial(black, new ConstantTexture(RGBColor(248,249,249)/255));
    Material* plantGroundMaterial = new LambertianMaterial(black, new ConstantTexture(RGBColor(80,63,37)/255));
    Material* plantAloeMaterial = new LambertianMaterial(black, new ConstantTexture(RGBColor(29,168,4)/255));

    // iPad and Macbook
    Material* deviceCaseMaterial = new PhongMaterial(new ConstantTexture(RGBColor(215,219,221)/255), 2);
    Material* macbookCaseMaterial = new LambertianMaterial(new ConstantTexture(RGBColor::rep(0)), new ConstantTexture(RGBColor(204,204,255)/255));
    Material* mousePadMaterial = new LambertianMaterial(black, new ConstantTexture(RGBColor(52,52,52)/255));

    Material* caseMaterial = new LambertianMaterial(new ConstantTexture(RGBColor::rep(0)), new ConstantTexture(RGBColor(225,193,110)/255));
    Material* caseButtonsMaterial = new PhongMaterial(new ConstantTexture(RGBColor(22,22,22)/255), 8);
    Material* caseInsideMaterial = new PhongMaterial(new ConstantTexture(RGBColor(81,0,255)/255), 2);

    Material* tableMaterial = new PhongMaterial(new ConstantTexture(RGBColor(167,90,33)/255), 1);

    Material* carpetMaterial = new LambertianMaterial(black, new ConstantTexture(RGBColor(210,143,47)/255));

    Material* chairMaterial = new LambertianMaterial(black, new ConstantTexture(RGBColor(88,78,118)/255));

    Material* wallMaterial = new LambertianMaterial(black, new ConstantTexture(RGBColor(215,210,255)/255));

    Material* shelfMaterial = new LambertianMaterial(black, new ConstantTexture(RGBColor(167,90,33)/255));

    Material* bookAMaterial = new LambertianMaterial(black, new ConstantTexture(RGBColor(139,220,255)/255));
    Material* bookBMaterial = new LambertianMaterial(black, new ConstantTexture(RGBColor(128,0,32)/255));

    Material* chairLegsMaterial = new LambertianMaterial(black, new ConstantTexture(RGBColor(50,50,50)/255));

    // //Bulbausaur
    Material* bulbasaurFlowerMaterial = new LambertianMaterial(black, new ConstantTexture(RGBColor(255,90,200)/255));
    Material* bulbasaurLeavesMaterial = new LambertianMaterial(black, new ConstantTexture(RGBColor(0,176,13)/255));
    Material* bulbasaurBodyMaterial = new LambertianMaterial(black, new ConstantTexture(RGBColor(116,217,212)/255));
    Material* bulbasaurEyesMaterial = new LambertianMaterial(black, new ConstantTexture(RGBColor(0,0,0)));
    Material* bulbasaurClawsMaterial = new LambertianMaterial(black, new ConstantTexture(RGBColor(1,1,1)));


    scene->add(getScene("keyboard_case.obj", keyboardCaseMaterial));
    scene->add(getScene("keyboard_blue_buttons.obj", keyboardBlueButtonsMaterial));
    scene->add(getScene("keyboard_red_buttons.obj", keyboardRedButtonsMaterial));
    scene->add(getScene("keyboard_white_buttons.obj", whiteLambertian));

    scene->add(getScene("table.obj", tableMaterial));
    scene->add(getScene("table_legs.obj", metailic));

    scene->add(getScene("mouse.obj", keyboardCaseMaterial));
    scene->add(getScene("mouse_pad.obj", mousePadMaterial));

    scene->add(getScene("cup.obj", glass));

    scene->add(getScene("monitor.obj", keyboardCaseMaterial));
    ImageTexture* monitor = new ImageTexture("models/valorant.png", ImageTexture::CLAMP);
    Material* valorant = new LambertianMaterial(monitor, black);
    Quad* monitorPic = new Quad(Point(-150,377,625), Vector(275,0,0), Vector(0,0,-185), nullptr, valorant);
    scene->add(monitorPic);

    scene->add(getScene("cup_pen.obj", plantPotMaterial));

    scene->add(getScene("iphone.obj", keyboardCaseMaterial));
    scene->add(getScene("ipad.obj", deviceCaseMaterial));

    scene->add(getScene("macbook.obj", macbookCaseMaterial));
    PerlinTexture* screenSaver = new PerlinTexture(RGBColor(0.5, 0, 0), RGBColor(0,0,0.5));
    screenSaver->addOctave(0.5f, 2.0f);
    screenSaver->addOctave(1.0f, 4.0f);
    Material* macbookScreen = new LambertianMaterial(screenSaver, black);
    Quad* macbookPic = new Quad(Point(-320,375,475), Vector(108,0,0), Vector(0,0,-75), nullptr, macbookScreen);
    scene->add(macbookPic);
    scene->add(getScene("macbook_screen.obj", blackLambertian));
    scene->add(getScene("macbook_keyboard.obj", keyboardCaseMaterial));

    scene->add(getScene("note_sticker.obj", carpetMaterial));
    scene->add(getScene("pen_black.obj", caseButtonsMaterial));
    scene->add(getScene("pen_white.obj", plantPotMaterial));
    scene->add(getScene("sketchpad.obj", keyboardCaseMaterial));

    scene->add(getScene("better_carpet.obj", carpetMaterial));

    scene->add(getScene("shelf.obj", shelfMaterial));
    scene->add(getScene("book_a.obj", bookBMaterial));
    scene->add(getScene("book_b.obj", bookAMaterial));

    scene->add(getScene("chair_top.obj", chairMaterial));
    scene->add(getScene("chair_legs.obj", chairLegsMaterial));

    scene->add(getScene("trashcan.obj", metailic));

    scene->add(getScene("case.obj", caseMaterial));
    scene->add(getScene("case_buttons.obj", caseButtonsMaterial));
    scene->add(getScene("case_inside.obj", caseInsideMaterial));
    scene->add(getScene("case_cooler.obj", keyboardCaseMaterial));
    scene->add(getScene("case_glass.obj", glass_2));
    //Cooler Light
    world.light.push_back(new PointLight(Point(270,360,470), RGBColor(5000,0,5000)*0.8));

    scene->add(getScene("frame_big.obj", plantPotMaterial));
    scene->add(getScene("frame_small.obj", plantPotMaterial));
    ImageTexture* nier = new ImageTexture("models/nier.png", ImageTexture::CLAMP);
    LambertianMaterial* picture1 = new LambertianMaterial(new ConstantTexture(RGBColor::rep(0.0f)), nier);
    Quad* nierPic = new Quad(Point(-363,442.5,820), Vector(-190,0,0), Vector(0,0,-220), nullptr, picture1);
    scene->add(nierPic);

    ImageTexture* cat = new ImageTexture("models/cat.png", ImageTexture::CLAMP);
    LambertianMaterial* picture2 = new LambertianMaterial(new ConstantTexture(RGBColor::rep(0.0f)), cat);
    Quad* catPic = new Quad(Point(-128,442.5,820), Vector(-135,0,0), Vector(0,0,-165), nullptr, picture2);
    scene->add(catPic);

    // //Plant
    scene->add(getScene("plant_pot.obj", plantPotMaterial));
    scene->add(getScene("plant_ground.obj", plantGroundMaterial));
    scene->add(getScene("plant_aloe.obj", plantAloeMaterial));

    //Walls
    scene->add(getScene("newscene.obj", wallMaterial));
    scene->add(getScene("window.obj", mirror));

    // // Bulbasaur
    scene->add(getScene("leaves.obj", bulbasaurLeavesMaterial));
    scene->add(getScene("body.obj", bulbasaurBodyMaterial));
    scene->add(getScene("clows.obj", bulbasaurClawsMaterial));
    scene->add(getScene("eyes.obj", bulbasaurEyesMaterial));
    scene->add(getScene("flower.obj", bulbasaurFlowerMaterial));

    world.scene = scene;
    world.light.push_back(new PointLight(Point(-11,-10,6.5)*200, RGBColor(5000000,5000000,5000000)*0.8));

    Material* coolerLightMaterial = new LambertianMaterial(new ConstantTexture(RGBColor(187,143,206)/255*300), black);
    Quad* coolerLight = new Quad(Point(0,0,1300), Vector(-100,0,0), Vector(0,100,0), nullptr, coolerLightMaterial);
    AreaLight als(coolerLight);
    world.light.push_back(&als);
    scene->add(coolerLight);

    world.light.push_back(new PointLight(Point(170,420,400), RGBColor(5000,0,5000)*0.8));
    world.light.push_back(new PointLight(Point(70,420,400), RGBColor(5000,0,5000)*0.8));
    world.light.push_back(new PointLight(Point(-30,420,400), RGBColor(5000,0,5000)*0.8));
    world.light.push_back(new PointLight(Point(-130,420,400), RGBColor(5000,0,5000)*0.8));
    world.light.push_back(new PointLight(Point(-230,420,400), RGBColor(5000,0,5000)*0.8));
    world.light.push_back(new PointLight(Point(-330,420,400), RGBColor(5000,0,5000)*0.8));

    //MAIN CAMERA
    Point p = Point(-2.5, -5, 6)*200;
    PerspectiveCamera cam(p, Vector(0.35,1,-0.6), Vector(0, 0, 1), pi*1.2/8, pi*1.2/5);

    RecursiveRayTracingIntegrator integrator(&world);
    Renderer engine(&cam, &integrator);
    engine.render(img);
    img.writeEXR("rendering_competition.exr");


}