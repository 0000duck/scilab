
/*

Copyright 2007 INRIA

Author : Sylvestre Ledru

This software is a computer program whose purpose is to hide the complexity
of accessing Java objects/methods from C++ code.

This software is governed by the CeCILL-B license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL-B
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-B license and that you accept its terms.
*/
#include "DrawableSubwinGL.hxx"

#include <string>
#include <iostream>
#include <stdlib.h>
#include <jni.h>

namespace org_scilab_modules_renderer_subwinDrawing {

// Returns the current env

JNIEnv * DrawableSubwinGL::getCurrentEnv() {
JNIEnv * curEnv = NULL;
this->jvm->AttachCurrentThread((void **) &curEnv, NULL);
return curEnv;
}
// Destructor

DrawableSubwinGL::~DrawableSubwinGL() {
JNIEnv * curEnv = NULL;
this->jvm->AttachCurrentThread((void **) &curEnv, NULL);

curEnv->DeleteGlobalRef(this->instance);
curEnv->DeleteGlobalRef(this->instanceClass);
}

// Constructors

DrawableSubwinGL::DrawableSubwinGL(JavaVM * jvm_) {
jmethodID constructObject = NULL ;
jobject localInstance ;
jclass localClass ;
const std::string className="org/scilab/modules/renderer/subwinDrawing/DrawableSubwinGL";
const std::string construct="<init>";
const std::string param="()V";
jvm=jvm_;

JNIEnv * curEnv = getCurrentEnv();

localClass = curEnv->FindClass( className.c_str() ) ;
if (localClass == NULL) {
std::cerr << "Could not get the Class " << className <<  std::endl;
exit(EXIT_FAILURE);
}

this->instanceClass = (jclass) curEnv->NewGlobalRef(localClass) ;
if (this->instanceClass == NULL) {
std::cerr << "Could not create a Global Ref of " << className <<  std::endl;
exit(EXIT_FAILURE);
}

constructObject = curEnv->GetMethodID( this->instanceClass, construct.c_str() , param.c_str() ) ;
if(constructObject == NULL){
std::cerr << "Could not retrieve the constructor of the class " << className << " with the profile : " << construct << param << std::endl;
exit(EXIT_FAILURE);
}

localInstance = curEnv->NewObject( this->instanceClass, constructObject ) ;
if(localInstance == NULL){
std::cerr << "Could not instance the object " << className << " with the constructor : " << construct << param << std::endl;
exit(EXIT_FAILURE);
}
 
this->instance = curEnv->NewGlobalRef(localInstance) ;
if(this->instance == NULL){
std::cerr << "Could not create a new global ref of " << className << std::endl;
exit(EXIT_FAILURE);
}

voiddisplayID=NULL; 
voidinitializeDrawingjintID=NULL; 
voidendDrawingID=NULL; 
voidshowID=NULL; 
voiddestroyjintID=NULL; 
voidsetFigureIndexjintID=NULL; 


}

// Generic methods


void DrawableSubwinGL::synchronize() {
if (getCurrentEnv()->MonitorEnter(instance) != JNI_OK) {
std::cerr << "Fail to enter monitor." << std::endl;
exit(EXIT_FAILURE);
}
}


void DrawableSubwinGL::endSynchronize() {
if ( getCurrentEnv()->MonitorExit(instance) != JNI_OK) {
std::cerr << "Fail to exit monitor." << std::endl;
exit(EXIT_FAILURE);
}
}

// Method(s)

void DrawableSubwinGL::display (){

JNIEnv * curEnv = getCurrentEnv();

if (this->voiddisplayID == NULL)
{
this->voiddisplayID = curEnv->GetMethodID(this->instanceClass, "display", "()V" ) ;
if (this->voiddisplayID == NULL) {
std::cerr << "Could not access to the method display" << std::endl;
exit(EXIT_FAILURE);
}
}
  (void) curEnv->CallVoidMethod( this->instance, voiddisplayID );

if (curEnv->ExceptionOccurred()) {
curEnv->ExceptionDescribe() ;
}


}

void DrawableSubwinGL::initializeDrawing (long figureIndex){

JNIEnv * curEnv = getCurrentEnv();

if (this->voidinitializeDrawingjintID == NULL)
{
this->voidinitializeDrawingjintID = curEnv->GetMethodID(this->instanceClass, "initializeDrawing", "(I)V" ) ;
if (this->voidinitializeDrawingjintID == NULL) {
std::cerr << "Could not access to the method initializeDrawing" << std::endl;
exit(EXIT_FAILURE);
}
}
  (void) curEnv->CallVoidMethod( this->instance, voidinitializeDrawingjintID ,figureIndex);

if (curEnv->ExceptionOccurred()) {
curEnv->ExceptionDescribe() ;
}


}

void DrawableSubwinGL::endDrawing (){

JNIEnv * curEnv = getCurrentEnv();

if (this->voidendDrawingID == NULL)
{
this->voidendDrawingID = curEnv->GetMethodID(this->instanceClass, "endDrawing", "()V" ) ;
if (this->voidendDrawingID == NULL) {
std::cerr << "Could not access to the method endDrawing" << std::endl;
exit(EXIT_FAILURE);
}
}
  (void) curEnv->CallVoidMethod( this->instance, voidendDrawingID );

if (curEnv->ExceptionOccurred()) {
curEnv->ExceptionDescribe() ;
}


}

void DrawableSubwinGL::show (){

JNIEnv * curEnv = getCurrentEnv();

if (this->voidshowID == NULL)
{
this->voidshowID = curEnv->GetMethodID(this->instanceClass, "show", "()V" ) ;
if (this->voidshowID == NULL) {
std::cerr << "Could not access to the method show" << std::endl;
exit(EXIT_FAILURE);
}
}
  (void) curEnv->CallVoidMethod( this->instance, voidshowID );

if (curEnv->ExceptionOccurred()) {
curEnv->ExceptionDescribe() ;
}


}

void DrawableSubwinGL::destroy (long figureIndex){

JNIEnv * curEnv = getCurrentEnv();

if (this->voiddestroyjintID == NULL)
{
this->voiddestroyjintID = curEnv->GetMethodID(this->instanceClass, "destroy", "(I)V" ) ;
if (this->voiddestroyjintID == NULL) {
std::cerr << "Could not access to the method destroy" << std::endl;
exit(EXIT_FAILURE);
}
}
  (void) curEnv->CallVoidMethod( this->instance, voiddestroyjintID ,figureIndex);

if (curEnv->ExceptionOccurred()) {
curEnv->ExceptionDescribe() ;
}


}

void DrawableSubwinGL::setFigureIndex (long figureIndex){

JNIEnv * curEnv = getCurrentEnv();

if (this->voidsetFigureIndexjintID == NULL)
{
this->voidsetFigureIndexjintID = curEnv->GetMethodID(this->instanceClass, "setFigureIndex", "(I)V" ) ;
if (this->voidsetFigureIndexjintID == NULL) {
std::cerr << "Could not access to the method setFigureIndex" << std::endl;
exit(EXIT_FAILURE);
}
}
  (void) curEnv->CallVoidMethod( this->instance, voidsetFigureIndexjintID ,figureIndex);

if (curEnv->ExceptionOccurred()) {
curEnv->ExceptionDescribe() ;
}


}

}
