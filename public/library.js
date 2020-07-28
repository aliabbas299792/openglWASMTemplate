function stringToTypedArray(input){
    const typedArray = new Uint8Array(input.length);
    input.split('').forEach((character, index) => typedArray[index] = character.charCodeAt(0));
    return typedArray;
}

if (typeof mergeInto !== 'undefined') mergeInto(LibraryManager.library, {
    getFile: function(filenamePtr, length) {
        const filename = String.fromCharCode(...Module.HEAPU8.slice(filenamePtr, filenamePtr+length));
        const returnData = stringToTypedArray(data[filename]);

        const buffer = Module._malloc(returnData.byteLength);
        Module.HEAPU8.set(returnData, buffer);
        return buffer;
    }
});