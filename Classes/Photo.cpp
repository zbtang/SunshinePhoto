#include "Photo.h"

Photo::Photo(int photoID):photoId(photoID),photoLife(0),currentState(eStateUnborn),hasConnectWithJiazi(false),jiaZiToConnect(NULL)
{}
Photo::~Photo()
{}