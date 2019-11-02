const test = require('./modulePath/main');

const files = ['C:\\files\\text.txt', 'C:\\files\\image.png']; // Пример массива путей к файламconst

location = 'C:\\location'; // Пример папки, в которую нужно скопировать файлы

function printProgress(text) {
    console.log(text);
} // Функция callback, выводящая информацию о скопированном файле. Пример text – “Файл C:\\files\\text.txt скопирован”.

function printSuccess(text) {
    console.log(text);
} // Функция callback, выводящая сообщение о завершении копирования

//test.copy(files, location, printProgress, printSuccess);