#include "myxml.h"

#include <QFile>
#include <QDomDocument>
#include <QDomProcessingInstruction>
#include <QDomText>
#include <QTextStream>
#include <QFileInfo>
#include <QDomNodeList>

#include <QDebug>

MyXML::MyXML(QString fileNmae)
{
    if(fileNmae.isEmpty())
        return;
    saveFileName = fileNmae;

    QFileInfo fileInfo(saveFileName);
    if(fileInfo.exists() && fileInfo.isFile())
        loadXML();  //文件存在，载入文件
    else
        creatXML(); //文件不存在，新创建一个文件
}

MyXML::~MyXML()
{

}

void MyXML::creatXML()
{
    if(saveFileName.isEmpty())
        return;

    QDomProcessingInstruction instruction;
    instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"GB2312\"");
    doc.appendChild(instruction);

    QDomElement root = doc.createElement("FileManager");
    root.appendChild(doc.createElement("FileList"));
    root.appendChild(doc.createElement("LastPalyFile"));
    doc.appendChild(root);

    QFile file(saveFileName);
    file.open(QIODevice::ReadWrite);
    QTextStream out(&file);
    doc.save(out,4);
    file.close();
}


void MyXML::loadXML()
{
    QFile file(saveFileName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        file.remove();
        creatXML();
        return;
    }
    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn)) {
        file.close();
        file.remove();
        doc.clear();
        creatXML();
        return;
    }
    file.close();
    QDomElement root = doc.documentElement();
    if (root.tagName() != "FileManager") {
       file.remove();
       doc.clear();
       creatXML();
    }
}

void MyXML::save()
{
    if(saveFileName.isEmpty())
        return;
    QFile file(saveFileName);
    file.resize(0);
    if(!file.open(QIODevice::ReadWrite))
        return;
    QTextStream out(&file);
    doc.save(out,4);
    file.close();
}

void MyXML::addElement(FileElement element)
{
    if(getElement(element.fileName,NULL))
        return;
    QDomElement newElement = doc.createElement("File");
    newElement.setAttribute("Class", element.fileClass);
    newElement.setAttribute("Position", element.lastPosition);
    newElement.setAttribute("Name", element.fileName);
    QDomElement filelist = doc.documentElement().firstChildElement("FileList");
    filelist.appendChild(newElement);
}

bool MyXML::getElement(QString fileName, FileElement *element)
{
    if (fileName.isEmpty())
        return false;
    QDomElement filelist = doc.documentElement().firstChildElement("FileList");
    QDomElement elt = filelist.firstChildElement("File");
    for (; !elt.isNull(); elt = elt.nextSiblingElement("File")) {
        if (elt.attribute("Name") == fileName) {
            if (element) {
                element->fileName       = fileName;
                element->lastPosition   = elt.attribute("Position").toLong();
                element->fileClass      = elt.attribute("Class").toInt();
            }
            return true;
        }
    }
    return false;
}

void MyXML::removeElement(QString fileName)
{
    if (fileName.isEmpty())
        return;
    QDomElement filelist = doc.documentElement().firstChildElement("FileList");
    QDomElement elt = filelist.firstChildElement("File");
    for (; !elt.isNull(); elt = elt.nextSiblingElement("File")) {
        if (elt.attribute("Name") == fileName) {
            filelist.removeChild(elt);
        }
    }
}

bool MyXML::replaceElement(FileElement element)
{
    QDomElement filelist = doc.documentElement().firstChildElement("FileList");
    QDomElement elt = filelist.firstChildElement("File");
    for (; !elt.isNull(); elt = elt.nextSiblingElement("File")) {
        if (elt.attribute("Name") == element.fileName) {
            elt.setAttribute("Position", element.lastPosition);
            return true;
        }
    }
    return false;
}

/**
 * @brief MyXML::getFileList 获取给定类别的所有文件的文件名列表
 * @param fileCalss 给定的类别，取值在0到9之间
 * @return 给定类别的所有文件的文件名列表
 */
QStringList MyXML::getFileList(int fileCalss)
{
    if(fileCalss < 0 || fileCalss > 9)
        fileCalss = 0;

    QStringList fileList;
    QDomElement filelist = doc.documentElement().firstChildElement("FileList");
    QDomElement elt = filelist.firstChildElement("File");
    for (; !elt.isNull(); elt = elt.nextSiblingElement("File")) {
        if(fileCalss == 0 || elt.attribute("Class").toInt() == fileCalss)
            fileList.append(elt.attribute("Name"));
    }
    return fileList;
}

void MyXML::setLastFile(FileElement element)
{
    QDomElement lastFile = doc.documentElement().firstChildElement("LastPalyFile");
    if(lastFile.isNull()) {
        lastFile = doc.createElement("LastPalyFile");
        doc.documentElement().appendChild(lastFile);
    }
    lastFile.setAttribute("Class", element.fileClass);
    lastFile.setAttribute("Position", element.lastPosition);
    lastFile.setAttribute("Name", element.fileName);
}

QString MyXML::getLastFile()
{
    QDomElement lastFile = doc.documentElement().firstChildElement("LastPalyFile");
    if(lastFile.isNull()) {
        return "";
    } else {
        return lastFile.attribute("Name");
    }
}

