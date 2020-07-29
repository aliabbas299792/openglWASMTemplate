function stringToTypedArray(input){
    const typedArray = new Uint8Array(input.length);
    input.split('').forEach((character, index) => typedArray[index] = character.charCodeAt(0)); //stores character codes of each character into the typed array
    return typedArray;
}

if (typeof mergeInto !== 'undefined') mergeInto(LibraryManager.library, {
    getFile: function(filenamePtr, length) {
        const filename = String.fromCharCode(...Module.HEAPU8.slice(filenamePtr, filenamePtr+length)); //uses the pointer and length to retrieve the filename
        const returnData = stringToTypedArray(data[filename]);

        const buffer = Module._malloc(returnData.byteLength); //allocates enough space to store the contents of the return character array
        Module.HEAPU8.set(returnData, buffer); //store the typed array in the heap

        Module.HEAPU8[buffer+returnData.byteLength] = 0;
        //marks the final character as 0 (NUL character/Null terminator, C++ uses this as a flag indicating the end of a string)
        //otherwise the C++ string will have a non-deterministic-ish end, so may include a bunch of random characters as well

        return buffer; //return this value (it's a pointer basically)
    }
});
