#include <vector>
#include <string>
class grid {
  double xcoordinate;
  double ycoordinate;
  bool   used;
}
class APC {
  bool promote;
  bool connect;
  string net;
  vector < AP > accesspoint;
}
class AP {
  double x;
  double y;
}
