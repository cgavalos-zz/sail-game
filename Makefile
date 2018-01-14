SRCS = WindowParameters.cpp SkyboxObject.cpp SkyboxObjectGraphicsComponent.cpp PlayerInputComponent.cpp UBOManager.cpp RigidObjectPhysicsComponent.cpp Line.cpp FileUtils.cpp Camera.cpp World.cpp RigidObjectGraphicsComponent.cpp ShaderMisc.cpp main.cpp RigidObject.cpp SkyParameters.cpp WaterSurfacePhysicsComponent.cpp TypeSize.cpp TestObject.cpp Plane.cpp Triangle.cpp Player.cpp VertexElementGraphicsComponent.cpp WaterSurface.cpp PointForce.cpp WaterSurfaceGraphicsComponent.cpp

EXNAME = SailGame
CFLAGS = -std=c++11 -o $(EXNAME)
LFLAGS = -lSDL2 -lGL -lGLEW
DFLAGS = -g -Wall
RFLAGS = -O2 -s

debug1:
	g++ main.cpp $(DFLAGS) $(CFLAGS) $(LFLAGS)

debug: main.cpp
	g++ $(SRCS) $(DFLAGS) $(CFLAGS) $(LFLAGS)

run:
	./$(EXNAME)

release:
	g++ $(SRCS) $(RFLAGS) $(CFLAGS) $(LFLAGS)

clean:
	$(RM) $(EXNAME)
