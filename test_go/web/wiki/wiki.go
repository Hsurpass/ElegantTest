// https://go-zh.org/doc/articles/wiki/

package main

import (
	"errors"
	"fmt"
	"io/ioutil"
	"net/http"
	"regexp"
	"text/template"
)

type Page struct {
	Title string
	Body  []byte
}

func (p *Page) save() error {
	filename := p.Title + ".txt"
	return ioutil.WriteFile(filename, p.Body, 0600)
}

func loadPage(title string) (*Page, error) {
	filename := title + ".txt"
	body, err := ioutil.ReadFile(filename)
	if err != nil {
		return nil, err
	}
	return &Page{Title: title, Body: body}, nil
}

func test_save_load_page() {
	p1 := &Page{Title: "TestPage", Body: []byte("This is a sample Page.")}
	p1.save()
	p2, _ := loadPage("TestPage")
	fmt.Println(string(p2.Body))
}

// 提前把模板全部解析出来，保存到内存中，是提升效率的一种方式
var templates = template.Must(template.ParseFiles("edit.html", "view.html"))

func renderTemplate_(w http.ResponseWriter, tmp string, p *Page) {
	err := templates.ExecuteTemplate(w, tmp+".html", p)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
	}
}
func renderTemplate(w http.ResponseWriter, tmp string, p *Page) {
	t, err := template.ParseFiles(tmp + ".html")
	fmt.Println(tmp, " renderTemplate, err:", err)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
	}
	err = t.Execute(w, p)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
	}
}

func viewHandler(w http.ResponseWriter, r *http.Request) {
	title, err := getTitle(w, r)
	if err != nil {
		return
	}
	// title := r.URL.Path[len("/view/"):]
	p, err := loadPage(title)
	fmt.Println("viewHandler err: ", err)
	if err != nil {
		http.Redirect(w, r, "/edit/"+title, http.StatusFound)
		return
	}
	// renderTemplate(w, "view", p)
	renderTemplate_(w, "view", p)
}

func editHandler(w http.ResponseWriter, r *http.Request) {
	title, err := getTitle(w, r)
	if err != nil {
		return
	}
	// title := r.URL.Path[len("/edit/"):]
	p, err := loadPage(title)
	fmt.Println("editHandler err: ", err)
	if err != nil {
		p = &Page{Title: title}
	}
	// renderTemplate(w, "edit", p)
	renderTemplate_(w, "edit", p)
}

func saveHandler(w http.ResponseWriter, r *http.Request) {
	title, err := getTitle(w, r)
	if err != nil {
		return
	}
	// title := r.URL.Path[len("/save/"):]
	body := r.FormValue("body")
	p := &Page{Title: title, Body: []byte(body)}
	err = p.save()
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}

	http.Redirect(w, r, "/view/"+title, http.StatusFound)
}

// 为了不让用户随便创建文件，可以利用正则表达式来约束文件名
var validPath = regexp.MustCompile("^/(edit|save|view)/([a-zA-Z0-9]+)$")

func getTitle(w http.ResponseWriter, r *http.Request) (string, error) {
	m := validPath.FindStringSubmatch(r.URL.Path)
	if m == nil {
		http.NotFound(w, r)
		return "", errors.New("Invalid Page Title")
	}
	return m[2], nil
}

func serve() {
	http.HandleFunc("/view/", viewHandler)
	http.HandleFunc("/edit/", editHandler)
	http.HandleFunc("/save/", saveHandler)

	http.ListenAndServe(":8000", nil)
}

func main() {
	// test_save_load_page()

	serve()
}
