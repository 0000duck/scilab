/* Allan CORNET */
/* Vincent COUVERT */
/* INRIA 2007 */
/* Utilities for writing JNIs which use datatypes not handled by SWIG */

/* String[] <--> char ** support */

%typemap(in) char ** (jint size) {
    int i = 0;
    size = (*jenv)->GetArrayLength(jenv, $input);
    $1 = (char **) MALLOC((size+1)*sizeof(char *));
    /* make a copy of each string */
    for (i = 0; i<size; i++) {
        jstring j_string = (jstring)(*jenv)->GetObjectArrayElement(jenv, $input, i);
        const char * c_string = (*jenv)->GetStringUTFChars(jenv, j_string, 0);
        $1[i] = MALLOC(strlen((c_string)+1)*sizeof(const char *));
        strcpy($1[i], c_string);
        (*jenv)->ReleaseStringUTFChars(jenv, j_string, c_string);
        (*jenv)->DeleteLocalRef(jenv, j_string);
    }
    $1[i] = 0;
}

/* This cleans up the memory we malloc'd before the function call */
%typemap(freearg) char ** {
    int i;
    for (i=0; i<size$argnum-1; i++)
      FREE($1[i]);
    FREE($1);
}

/* This allows a C function to return a char ** as a Java String array */
%typemap(out) char ** {
    int i;
    int len=0;
    jstring temp_string;
    const jclass clazz = (*jenv)->FindClass(jenv, "java/lang/String");

    while ($1[len]) len++;    
    jresult = (*jenv)->NewObjectArray(jenv, len, clazz, NULL);
    /* exception checking omitted */

    for (i=0; i<len; i++) {
      temp_string = (*jenv)->NewStringUTF(jenv, *result++);
      (*jenv)->SetObjectArrayElement(jenv, jresult, i, temp_string);
      (*jenv)->DeleteLocalRef(jenv, temp_string);
    }
}

/* These 3 typemaps tell SWIG what JNI and Java types to use */
%typemap(jni) char ** "jobjectArray"
%typemap(jtype) char ** "String[]"
%typemap(jstype) char ** "String[]"


/* These 2 typemaps handle the conversion of the jtype to jstype typemap type
   and visa versa */
%typemap(javain) char ** "$javainput"
%typemap(javaout) char ** {
    return $jnicall;
  }

/* String[] <--> char ** support */

/* boolean <--> BOOL support */

%typemap(in) BOOL {
	if ($input == JNI_TRUE) $1 = TRUE;
	else $1 = FALSE;
}

%typemap(out) BOOL {
 if ($1) $result = JNI_TRUE   ;
 else  $result = JNI_FALSE   ;
}

/* This typemap tell SWIG what JNI and Java types to use */
%typemap(jtype) BOOL "boolean"
%typemap(jstype) BOOL "boolean"
%typemap(jni) BOOL "jboolean"

/* These 2 typemaps handle the conversion of the jtype to jstype typemap type
   and visa versa */
%typemap(javaout) BOOL {
    return $jnicall;
  }
%typemap(javain) BOOL "$javainput";

/* boolean <--> BOOL support */
