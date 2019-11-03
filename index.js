const addon = require('bindings')('cp_module');

const files = ['D:\\Programming\\test\\text.txt', 'D:\\Programming\\test\\image.jpg']; // Пример массива путей к файлам

const location = 'D:\\Programming\\location'; // Пример папки, в которую нужно скопировать файлы

function printProgress(text) {
    console.log(text);
} // Функция callback, выводящая информацию о скопированном файле. Пример text – “Файл C:\\files\\text.txt скопирован”.

function printSuccess(text) {
    console.log(text);
} // Функция callback, выводящая сообщение о завершении копирования

addon.copy(files, location, printProgress, printSuccess);
