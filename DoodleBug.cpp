#include <iostream>
using namespace std;

const int worldsize = 20;
const int initialAnts = 100;
const int initialDoodles = 5;
const int Doodle = 1;
const int Antt = 2;
const int breedAnt = 3;
const int breedDoodle = 8;
const int starveDoodle = 3;

class Organism;
class Doodlebug;
class Ant;

class World{
  friend class Organism;
  friend class Doodlebug;
  friend class Ant;
  public:
    World();
    ~World();
    Organism* getAt(int x, int y);
    void setAt(int x, int y, Organism *org);
    void display();
    void Simulatestep();
  private:
    Organism* grid[worldsize][worldsize];
};

class Organism{
  friend class World;
  public:
    Organism(){}
    Organism(World *world, int x, int y);
    ~Organism();
    virtual void breed() = 0;
    virtual void move() = 0;
    virtual int getType() =0;
    virtual bool starve() = 0;
  protected:
    int x, y;
    bool moved;
    int breedTicks;
    World *world;
};

World::World(){
  for(int i=0; i<worldsize; i++){
    for (int j=0; j<worldsize;j++){
      grid[i][j] = NULL;
    }
  }
}
World::~World(){
  for(int i=0; i<worldsize; i++){
    for (int j=0; j<worldsize;j++){
      if (grid[i][j] != NULL){
        delete[] grid[i][j];
      }
    }
  }
}

Organism* World::getAt(int x, int y){
  return grid[x][y];
}

void World::setAt(int x, int y, Organism* org){
  grid[x][y] = org;
}

void World::display(){
  for(int i=0; i<worldsize; i++){
    for(int j=0; j<worldsize; j++){
      if(grid[i][j] == NULL){
        cout << ".";
      }
      else if(grid[i][j]->getType() == Antt){
        cout << "O";
      }
      else {
        cout << "X";
      }
    }
    cout << endl;
  }
}

void World::Simulatestep(){
  for (int i=0; i<worldsize; i++){
    for(int j=0; j<worldsize; j++){
      if(grid[i][j] != NULL){
        grid[i][j]->moved = false;
      }
    }
  }
  for (int i=0; i<worldsize; i++){
    for(int j=0; j<worldsize; j++){
      if(grid[i][j] != NULL && (grid[i][j] -> getType() == Doodle)){
        if(grid[i][j]->moved == false){
          grid[i][j]->moved = true;
          grid[i][j]->move();
        }
      }
    }
  }
  for (int i=0; i<worldsize; i++){
    for(int j=0; j<worldsize; j++){
      if(grid[i][j] != NULL && (grid[i][j] -> getType() == Antt)){
        if(grid[i][j]->moved == false){
          grid[i][j]->moved = true;
          grid[i][j]->move();
        }
      }
    }
  }
  for (int i=0; i<worldsize; i++){
    for(int j=0; j<worldsize; j++){
      if(grid[i][j] != NULL && (grid[i][j] -> getType() == Doodle)){
        if(grid[i][j]->starve()){
          delete (grid[i][j]);
          grid[i][j]->moved = true;
          grid[i][j]=NULL;
        }
      }
    }
  }
  for (int i=0; i<worldsize; i++){
    for(int j=0; j<worldsize; j++){
      if(grid[i][j] != NULL && (grid[i][j] -> moved == true)){
        if(grid[i][j]->moved == false){
          grid[i][j]->breed();
        }
      }
    }
  }
}

Organism::Organism(World *world, int x, int y){
  this->world = world;
  moved = false;
  this->x = x;
  this->y = y;
  world->setAt(x,y,this);
}
Organism::~Organism(){

}

class Ant:public Organism{
  friend class World;
  public:
    Ant();
    Ant(World *world, int x, int y);
    void breed();
    void move();
    int getType();
    bool starve(){return false;}
};

Ant::Ant():Organism(){}
Ant::Ant(World *world, int x, int y):Organism(world, x, y){}

void Ant::move(){
  int direction = rand() %4;
  if (direction == 0){
    if(y>0 && world->getAt(x,y-1) == NULL){
      world->setAt(x,y-1, world->getAt(x,y));
      world->setAt(x,y,NULL);
      y--;
    }
  }
  else if (direction == 1){
      if(x>0 && world->getAt(x-1,y) == NULL){
        world->setAt(x-1,y, world->getAt(x,y));
        world->setAt(x,y,NULL);
        x--;
      }
    }
    else if (direction == 2){
      if(y<20 && world->getAt(x,y+1) == NULL){
        world->setAt(x,y+1, world->getAt(x,y));
        world->setAt(x,y,NULL);
        y++;
      }
    }
    else {
      if(x<20 && world->getAt(x+1,y) == NULL){
        world->setAt(x+1,y, world->getAt(x,y));
        world->setAt(x,y,NULL);
        x++;
      }
    }
}
int Ant::getType(){
  return Antt;
}
void Ant::breed(){
  breedTicks++;
  if(breedTicks == breedAnt){
    breedTicks = 0;
    if((y>0) && (world ->getAt(x,y-1) == NULL)){
      Ant *newAnt = new Ant(world, x, y-1);
    }
    else if((y<worldsize-1) && (world ->getAt(x,y+1) == NULL)){
      Ant *newAnt = new Ant(world, x, y+1);
    }
    else if((x>0) && (world ->getAt(x-1,y) == NULL)){
      Ant *newAnt = new Ant(world, x-1, y);
    }
    else if((x<worldsize-1) && (world ->getAt(x+1,y) == NULL)){
      Ant *newAnt = new Ant(world, x+1, y);
    }
  }
}
class Doodlebug:public Organism{
  friend class World;
  public:
    Doodlebug();
    Doodlebug(World *world, int x, int y);
    void breed();
    void move();
    int getType();
    bool starve();
  private:
    int starveNum;
};

Doodlebug::Doodlebug():Organism(){
  starveNum = 0;
}
Doodlebug::Doodlebug(World *world, int x, int y):Organism(world, x, y){
  starveNum = 0;
}

void Doodlebug::move(){
  if((y>0) && (world ->getAt(x,y-1) != NULL) && (world->getAt(x,y-1)->getType() == Antt)){
    delete (world ->grid[x][y-1]);
    world->grid[x][y-1] = this;
    world -> setAt(x,y,NULL);
    starveNum = 0;
    y--;
    return;
  }
  else if((y<worldsize) && (world ->getAt(x,y+1) != NULL) && (world->getAt(x,y+1)->getType() == Doodle)){
    delete (world ->grid[x][y+1]);
    world->grid[x][y+1] = this;
    world -> setAt(x,y,NULL);
    starveNum = 0;
    y++;
    return;
  }
  else if((x<worldsize) && (world ->getAt(x+1,y) != NULL) && (world->getAt(x+1,y)->getType() == Antt)){
    delete (world ->grid[x+1][y]);
    world->grid[x+1][y] = this;
    world -> setAt(x,y,NULL);
    starveNum = 0;
    x++;
    return;
  }
  else if((x>0) && (world ->getAt(x-1,y) != NULL) && (world->getAt(x-1,y)->getType() == Antt)){
    delete (world ->grid[x-1][y]);
    world->grid[x-1][y] = this;
    world -> setAt(x,y,NULL);
    starveNum = 0;
    x--;
    return;
  }
  int direction = rand() %4;
  if (direction == 0){
    if(y>0 && world->getAt(x,y-1) == NULL){
      world->setAt(x,y-1, world->getAt(x,y));
      world->setAt(x,y,NULL);
      y--;
    }
  }
  else if (direction == 1){
    if(x>0 && world->getAt(x-1,y) == NULL){
      world->setAt(x-1,y, world->getAt(x,y));
      world->setAt(x,y,NULL);
      x--;
    }
  }
  else if (direction == 2){
    if(y<20 && world->getAt(x,y+1) == NULL){
      world->setAt(x,y+1, world->getAt(x,y));
      world->setAt(x,y,NULL);
      y++;
    }
  }
  else {
    if(x<20 && world->getAt(x+1,y) == NULL){
      world->setAt(x+1,y, world->getAt(x,y));
      world->setAt(x,y,NULL);
      x++;
    }
  }
  starveNum++;
}
int Doodlebug::getType(){
  return Doodle;
}
void Doodlebug::breed(){
  breedTicks++;
  if(breedTicks == breedDoodle){
    breedTicks=0;
    if((y>0) && (world->getAt(x,y-1)==NULL)){
      Doodlebug *newDoodlebug = new Doodlebug(world, x, y-1);
    }
    else if((y<worldsize) && (world->getAt(x,y+1)==NULL)){
      Doodlebug *newDoodlebug = new Doodlebug(world, x, y+1);
    }
    else if((x>0) && (world->getAt(x-1,y)==NULL)){
      Doodlebug *newDoodlebug = new Doodlebug(world, x-1, y);
    }
    else if((x<worldsize) && (world->getAt(x+1,y)==NULL)){
    Doodlebug *newDoodlebug = new Doodlebug(world, x+1, y);
    }
  }
}

bool Doodlebug::starve(){
  if(starveNum > starveDoodle){
    return true;
  }
  else{
    return false;
  }
}

int main(){
  string s;
  srand(time(NULL));
  World w;

  int antcount = 0;
  while(antcount<initialAnts){
    int x=rand() % worldsize;
    int y=rand() % worldsize;
    if(w.getAt(x,y)==NULL){
      antcount++;
      Ant *Tony = new Ant(&w, x, y);
    }
  }

  int doodlecount = 0;
  while(doodlecount<initialDoodles){
    int x=rand() % worldsize;
    int y=rand() % worldsize;
    if(w.getAt(x,y)==NULL){
      doodlecount++;
      Doodlebug *Brad = new Doodlebug(&w, x, y);
    }
  }

  while(true){
    w.display();
    w.Simulatestep();
    cout << endl << "Press enter for next step" << endl;
    getline(cin,s);
  }
  return 0;
}
