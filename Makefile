CXX = g++
 
EXEC = raytracer
OBJECTS = main.o Vect.o Ray.o Camera.o Light.o Color.o Sphere.o Plane.o Object.o Source.o Intersection.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}
	./${EXEC}
	open -a Preview.app scene.bmp

-include ${DEPENDS}


.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}


	
