<?php

require_once 'classTextile.php';
require_once drupal_get_path('module', 'eca_main') . '/includes.inc';

class TextileExt extends Textile
{
  function graf($text)
    {
        // handle normal paragraph text
        if (!$this->lite) {
            $text = $this->noTextile($text);
            $text = $this->code($text);
        }

        $text = $this->links($text);
        if (!$this->noimage)
            $text = $this->image($text);

        if (!$this->lite) {
            $text = $this->lists($text);
            $text = $this->table($text);
        }

        $text = $this->span($text);
        $text = $this->footnoteRef($text);
        $text = $this->sourceRef($text); //walter
        $text = $this->glyphs($text);
        return rtrim($text, "\n");
    }

  function span($text)
    {
        $qtags = array('\*\*','\*','\?\?','-','__','_','%','\+','~','\^', '\/'); //walter
        $pnct = ".,\"'?!;:";

        foreach($qtags as $f) {
            $text = preg_replace_callback("/
                (?:^|(?<=[\s>$pnct])|([{[]))
                ($f)(?!$f)
                ({$this->c})
                (?::(\S+))?
                ([^\s$f]+|\S[^$f\n]*[^\s$f\n])
                ([$pnct]*)
                $f
                (?:$|([\]}])|(?=[[:punct:]]{1,2}|\s))
            /x", array(&$this, "fSpan"), $text);
        }
        return $text;
    }

// -------------------------------------------------------------
    function fSpan($m)
    {
        $qtags = array(
            '*'  => 'strong',
            '**' => 'b',
            '??' => 'cite',
            '_'  => 'em',
            '__' => 'i',
            '-'  => 'del',
            '%'  => 'span',
            '+'  => 'ins',
            '~'  => 'sub',
            '^'  => 'sup',
            '/'  => 'span', //walter
        );

        list(,, $tag, $atts, $cite, $content, $end) = $m;
        $tempTag = $tag;
        $tag = $qtags[$tag];
        $atts = $this->pba($atts);
        $atts .= ($cite != '') ? 'cite="' . $cite . '"' : '';
        $atts .= ($tempTag == '/') ? ' class="biography-label"' : '';
        $out = "<$tag$atts>$content$end</$tag>";

//      $this->dump($out);

        return $out;

    }
    
    function fLink($m)
    {
        list(, $pre, $atts, $text, $title, $url, $slash, $post) = $m;

        $url = $this->checkRefs($url);

        $atts = $this->pba($atts);
        $atts .= ($title != '') ? ' title="' . $this->encode_html($title) . '"' : '';

        if (!$this->noimage)
            $text = $this->image($text);

        $text = $this->span($text);
        $text = $this->glyphs($text);

        $url = $this->relURL($url);
        
        if( preg_match("/Agent|Exhibition|Artwork|Collective|Award|Institution|Publication|Algorithm/i", $url) ){
          
          $url = str_replace('@', '/', $url);
          
          if( ! preg_match("/Agent|Exhibition|Artwork/i", $url) ){
            $atts .= " class=\"dialog-link\"";
          }          
        }      
        
        $out = '<a href="' . $this->encode_html($url . $slash) . '"' . $atts . $this->rel . '>' . $text . '</a>' . $post;

        // $this->dump($out);
        return $this->shelve($out);

    }
    
    function sourceRef($text)
    {
        //                    [source: (1-n mal eine ziffer) (optional:#) (0-n mal eine ziffer) ] (optional:whitespace)
        return preg_replace('/\[source:([0-9]+)(#)?([0-9]*)\](\s)?/Ue',
            '$this->sourceLink(\'\1\',\'\3\')', $text);
    }

// -------------------------------------------------------------
    function sourceLink($id, $t)
    {
        $title = _eca_get_publication_title($id);
        $output .= 'Source: ';
        $output .= l(_filter_url_trim($title, URL_LENGTH), 'publication/' . $id, array( 'attributes' => array('title' => $title, 'class' => 'dialog-link' )) );
        $output .= ' (p. ' .$t .')';
        return $output;
    }

} // end class

?>
