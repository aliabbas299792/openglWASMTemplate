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
        return buffer; //return this value (it's a pointer basically)
    }
});
