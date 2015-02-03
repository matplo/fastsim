%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% This class for Initial Stages 2014 (is2014.lbl.gov) conference proceedings was 
% created with use of tex examples from http://www.LaTeXTemplates.com
% Tex file example by: Frits Wenneker (http://www.howtotex.com)
% License: CC BY-NC-SA 3.0 (http://creativecommons.org/licenses/by-nc-sa/3.0/)
% Class by MP at is2014-help@lists.lbl.gov
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{is2014}[2014/02/02 IS2014 Class]
%% Article options
\DeclareOption{11pt}{
  \PassOptionsToClass{\CurrentOption}{article}
}

%% Fallback
\DeclareOption*{
\ClassWarning{is2014}{Unknown option '\CurrentOption'}
}
  
%% Execute default options
\ExecuteOptions{11pt}

%% Process given options
\ProcessOptions\relax

%% Load base
%%\LoadClass[a4paper]{article}
\LoadClass[twoside]{article}

%% Load additional packages and commands.
%%\RequirePackage{custom}
\RequirePackage{microtype} % Slightly tweak font spacing for aesthetics
\RequirePackage[hmarginratio=1:1,right=25mm,top=32mm,columnsep=8mm]{geometry} % Document margins
\RequirePackage{multicol} % Used for the two-column layout of the document
\RequirePackage{booktabs} % Horizontal rules in tables
\RequirePackage{float} % Required for tables and figures in the multi-column environment - they need to be placed in specific locations with the [H] (e.g. \begin{table}[H])
\RequirePackage{hyperref} % For hyperlinks in the PDF
\RequirePackage{lastpage,refcount} % Count pages
\RequirePackage{graphicx} % For graphics jpg, pdf etc.
\RequirePackage{epstopdf} % Convert from eps to pdf on the fly
\RequirePackage{paralist} % Used for the compactitem environment which makes bullet points with less space between them
\RequirePackage{abstract} % Allows abstract customization
\RequirePackage{titlesec} % Allows customization of titles
\RequirePackage{lipsum} % Package to generate dummy text throughout this template
\RequirePackage{ifthen} % Used for custom head depending on the page number
\RequirePackage{fancyhdr} % Headers and footers

%% Additional TeX/LaTeX code...

\graphicspath{{./}{./figures/}} % Find figures in the figures directory
\renewcommand{\abstractnamefont}{\normalfont\bfseries} % Set the "Abstract" text to bold
\renewcommand{\abstracttextfont}{\normalfont\small\itshape} % Set the abstract itself to small italic text
\renewcommand\thesection{\Roman{section}} % Roman numerals for the sections
\renewcommand\thesubsection{\Roman{subsection}} % Roman numerals for subsections
\titleformat{\section}[block]{\large\scshape\centering}{\thesection.}{1em}{} % Change the look of the section titles
\titleformat{\subsection}[block]{\large}{\thesubsection.}{1em}{} % Change the look of the section titles

\RequirePackage{etoolbox}
\patchcmd{\@maketitle}{\@title}{\vspace{-15mm}\fontsize{14pt}{10pt}\selectfont\textbf{\@title{}}}{}{}
\patchcmd{\@maketitle}{\@author}{\large \@author{}}{}{}
\pagestyle{fancy} % All pages have headers and footers
\lhead{}
\chead{\ifthenelse{\value{page}=1}{Conference on the 
Initial Stages in High-Energy Nuclear Collisions $\bullet$ 3-7 December, 2014}{}}
\rhead{}
\lfoot{\ifthenelse{\value{page}=1}{\url{http:\\\\is2014.lbl.gov}}{}}
\cfoot{}
\rfoot{Page \thepage\ of \pageref{LastPage} }
\renewcommand{\headrulewidth}{0pt}
\renewcommand{\footrulewidth}{0pt}

\endinput
